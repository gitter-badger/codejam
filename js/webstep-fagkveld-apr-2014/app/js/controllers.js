'use strict';

/* Controllers */

angular.module('myApp.controllers', [])
  .controller('MyCtrl1', function($scope, $http) {
    $scope.foo = "test";
    $http.get("/api/v1/users").success(function (data) {
        $scope.cvUsers = [];
        angular.forEach(data, function(user) {
            var u = {
                "userName" : user.name,
                "userId"   : user.user_id,
                "cvId"     : user.default_cv_id
                };
            $scope.cvUsers.push(u);
        });
    });
  })
  .controller('MyCtrl2', function($scope, $routeParams, $http) {
    $scope.userId = $routeParams.userId;
    $http.get("/api/v1/cvs/" + $routeParams.userId + "/" + $routeParams.cvId).success(function (data) {
        var experienceList = {};
        angular.forEach(data.project_experiences, function(experience) {
            var years;
            var yearTo = parseInt(experience.year_to);
            var yearFrom = parseInt(experience.year_from);
            if (!yearTo && !yearFrom) {
                years = 1;
            } else {
                if (!yearTo) yearTo = new Date().getFullYear();
                years = yearTo - yearFrom;
            }
            if (!years) years = 1;
            angular.forEach(experience.tags, function(tag) {
                if (!experienceList[tag]) experienceList[tag] = 0;
                experienceList[tag] += years;
            });
        });
        $scope.experienceList = experienceList;
    });
  });
