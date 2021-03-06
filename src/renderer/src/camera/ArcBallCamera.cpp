#include "renderer/camera/ArcBallCamera.h"
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <math.h>


namespace renderer
{

#ifndef M_PI
const float M_PI = glm::pi<float>();
#endif

ArcBallCamera::ArcBallCamera():
    Camera(),
    radius_(2.0f),
    phi_(3.0f * M_PI / 4.0f),
    theta_(M_PI)
{
    computePosition();
}
ArcBallCamera::~ArcBallCamera()
{

}

float ArcBallCamera::getRadius() const
{
    return radius_;
}

void ArcBallCamera::setRadius(float radius)
{
    radius_ = radius;
    computePosition();
}

float ArcBallCamera::getPhi() const
{
    return phi_;
}

void ArcBallCamera::setPhi(float phi)
{
    phi_ = std::max(std::min(static_cast<float>(M_PI - 0.01f), phi), 0.01f);
    computePosition();
}

float ArcBallCamera::getTheta() const
{
    return theta_;
}

void ArcBallCamera::setTheta(float theta)
{
    if(std::abs(theta) > 2 * M_PI)
    {
        theta_ = std::abs(theta) - 2 * M_PI;
    }

    theta_ = theta;
    computePosition();
}

void ArcBallCamera::setCenter(const glm::vec3& center)
{
    Camera::setCenter(center);
    computePolar();
    computePosition();
}

void ArcBallCamera::setPosition(const glm::vec3& position)
{
    Camera::setPosition(position);
    computePolar();
}

void ArcBallCamera::incrementPhi(float phiStep)
{
    setPhi(phi_ - phiStep);
}

void ArcBallCamera::incrementTheta(float thetaStep)
{
    setTheta(theta_ + thetaStep);
}

void ArcBallCamera::incrementRadius(float radiusStep)
{
    setRadius(radius_ + radiusStep);
}

void ArcBallCamera::computePosition()
{
    position_.x = radius_ * sin(phi_) * cos(theta_);
    position_.y = radius_ * sin(phi_) * sin(theta_);
    position_.z = radius_ * cos(phi_);

    Camera::setPosition(position_ + center_);
}

void ArcBallCamera::computePolar()
{
    glm::vec3 positionFromCenter = position_ - center_;
    radius_ = positionFromCenter.length();
    theta_ = atan(position_.y / position_.x);
    phi_ = atan((pow(position_.x, 2) + pow(position_.y, 2)) / position_.z);
}

}


