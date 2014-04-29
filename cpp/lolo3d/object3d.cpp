#include "object3d.h"

#include "glsl_utils.h"
#include "wavefront_loader.h"
#include <glm/gtc/matrix_transform.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

map<string, Object3D::Material> Object3D::materials;

Object3D::Object3D(const string & filename)
{
    WavefrontLoader::loadOBJ(filename, this);
    setAnimation("idle");

    //for (auto & it : groups) {
	for (map<string, Group>::iterator it = groups.begin(); it != groups.end(); ++it) {
        Group & group = it->second;
        GLuint & vertexBuffer = group.vertexBuffer;
        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * group.vertices.size(), group.vertices.data(), GL_STATIC_DRAW);
        group.vertices.clear();
    }

    modelMatrixUniformLocation = glGetUniformLocation(GLSLUtils::programId, "uModelMatrix");
    viewMatrixUniformLocation = glGetUniformLocation(GLSLUtils::programId, "uViewMatrix");
    projectionMatrixUniformLocation = glGetUniformLocation(GLSLUtils::programId, "uProjectionMatrix");
    samplerUniformLocation = glGetUniformLocation(GLSLUtils::programId, "uSampler");
    enableTextureUniformLocation = glGetUniformLocation(GLSLUtils::programId, "uEnableTexture");
    colorUniformLocation = glGetUniformLocation(GLSLUtils::programId, "uColor");
}

Object3D::~Object3D()
{
	//for (auto & it : groups) {
	for (map<string, Group>::iterator it = groups.begin(); it != groups.end(); ++it) {
        Group & group = it->second;
        glDeleteBuffers(1, &group.vertexBuffer);
    }
}

void Object3D::render(const mat4 & viewMatrix, const mat4 & projectionMatrix)
{
    glEnableVertexAttribArray(ATTRIB_POSITION);
    glEnableVertexAttribArray(ATTRIB_NORMAL);
    glEnableVertexAttribArray(ATTRIB_TEXCOORD);

    mat4 modelMatrix = glm::translate(mat4(), vec3(position.x, 0, position.y));

    if (rootGroup == "") {
        //for (auto & it : groups) {
		for (map<string, Group>::iterator it = groups.begin(); it != groups.end(); ++it) {
            Group & group = it->second;
            renderGroup(group, modelMatrix, viewMatrix, projectionMatrix);
        }
    } else {
        findGroup(rootGroup, modelMatrix, viewMatrix, projectionMatrix);
    }

    if (animations.count(animation)) {
        int from = animations.at(animation).first;
        int to = animations.at(animation).second;
        frame++;
        if (frame > to)
            frame = from;
    }

    glDisableVertexAttribArray(ATTRIB_POSITION);
    glDisableVertexAttribArray(ATTRIB_NORMAL);
    glDisableVertexAttribArray(ATTRIB_TEXCOORD);
}

void Object3D::findGroup(const string & groupName, const mat4 & modelMatrix, const mat4 & viewMatrix, const mat4 & projectionMatrix)
{
    Group & group = groups[groupName];
    mat4 modelMatrixResult = evaluateFrame(modelMatrix, group);

    renderGroup(group, modelMatrixResult, viewMatrix, projectionMatrix);

	//for (auto & childGroupName : group.children) {
	for (vector<string>::iterator it = group.children.begin(); it != group.children.end(); ++it) {
        findGroup(*it, modelMatrixResult, viewMatrix, projectionMatrix);
    }
}

void Object3D::renderGroup(const Group & group, const mat4 & modelMatrix, const mat4 & viewMatrix, const mat4 & projectionMatrix)
{
    setMaterial(group.material);

    glBindBuffer(GL_ARRAY_BUFFER, group.vertexBuffer);
    glVertexAttribPointer(ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(sizeof(GLfloat) * 3));
    glVertexAttribPointer(ATTRIB_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(sizeof(GLfloat) * 6));

    glUniformMatrix4fv(modelMatrixUniformLocation, 1, GL_FALSE, &modelMatrix[0][0]);
    glUniformMatrix4fv(viewMatrixUniformLocation, 1, GL_FALSE, &viewMatrix[0][0]);
    glUniformMatrix4fv(projectionMatrixUniformLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

    glMultiDrawArrays(GL_TRIANGLES, group.faceFirst.data(), group.faceCount.data(), GLsizei(group.faceFirst.size()));
}

void Object3D::setMaterial(const string & material)
{
    glUniform4fv(colorUniformLocation, 1, &materials[material].diffuse[0]);

    if (materials[material].texture != "") {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, materials[material].textureId);
        glUniform1i(samplerUniformLocation, 0); // GL_TEXTURE0
        glUniform1i(enableTextureUniformLocation, true);
    } else {
        glUniform1i(enableTextureUniformLocation, false);
    }
}

mat4 Object3D::interpolate(mat4 & mat, map<int, vec4> & keyFrames, TransformationType type)
{
    if (!animations.count(animation)) return mat;

    int prevKey = animations.at(animation).first;

//	for (auto & keyFrame : keyFrames) {
    for (map<int, vec4>::iterator it = keyFrames.begin(); it != keyFrames.end(); ++it) {
        if (prevKey > frame) break;
        if (it->first < animations.at(animation).first) continue;

        float alpha = (frame < it->first) ? float(frame - prevKey) / (it->first - prevKey) : 1.0f;
        alpha = sin(alpha * float(M_PI_2));

        if (type == TRANSLATE)
            mat = glm::translate(mat, glm::mix(vec3(), vec3(it->second), alpha));
        else if (type == SCALE)
            mat = glm::scale(mat, glm::mix(vec3(1), vec3(it->second), alpha));
        else
            mat = glm::rotate(mat, glm::mix(0.0f, it->second.x, alpha), vec3(it->second.yzw));

        prevKey = it->first;
    }

    return mat;
}

mat4 Object3D::evaluateFrame(const mat4 & modelMatrix, Group & group)
{
    vec3 pivot = group.pivot;

    mat4 result(modelMatrix);
    result = glm::translate(result, pivot);
    result = interpolate(result, group.translationKeyFrames, TRANSLATE);
    result = interpolate(result, group.scaleKeyFrames, SCALE);
    result = interpolate(result, group.rotationKeyFrames, ROTATE);
    result = glm::translate(result, -pivot);

    return result;
}

void Object3D::setAnimation(const string & animation)
{
    this->animation = animation;

    if (animations.count(animation))
        frame = animations.at(animation).first;
    else
        frame = 0;
}