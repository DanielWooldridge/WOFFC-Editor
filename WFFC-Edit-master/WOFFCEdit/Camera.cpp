#include "Camera.h"
#include <cmath>  // For sin() and cos()

Camera::Camera()
{
    Init();
}

Camera::~Camera() {}

void Camera::Init()
{
     m_movespeed = 0.30;
     m_camRotRate = 3.0;

     //camera
     m_camPosition.x = 0.0f;
     m_camPosition.y = 3.7f;
     m_camPosition.z = -3.5f;

     m_camOrientation.x = 0;
     m_camOrientation.y = 0;
     m_camOrientation.z = 0;

     m_camLookAt.x = 0.0f;
     m_camLookAt.y = 0.0f;
     m_camLookAt.z = 0.0f;

     m_camLookDirection.x = 0.0f;
     m_camLookDirection.y = 0.0f;
     m_camLookDirection.z = 0.0f;

     m_camRight.x = 0.0f;
     m_camRight.y = 0.0f;
     m_camRight.z = 0.0f;

     m_camOrientation.x = 0.0f;
     m_camOrientation.y = 0.0f;
     m_camOrientation.z = 0.0f;

     m_isArcballOn = false;
     arcballTarget = DirectX::SimpleMath::Vector3::Zero;
}

void Camera::Update(bool forward, bool back, bool left, bool right, bool rotLeft, bool rotRight, bool RB, POINT mouse, bool arcCamEnabled)
{
    DirectX::SimpleMath::Vector3 planarMotionVector = m_camLookDirection;
    planarMotionVector.y = 0.0;

    if (m_isArcballOn)
    {
        CreateArcball(1.0f / 60.0f);
        return; // no need for other input
    }

    if (rotRight)
    {
        m_camOrientation.y -= m_camRotRate;
    }
    if (rotLeft)
    {
        m_camOrientation.y += m_camRotRate;
    }

    if (RB)
    {

        GetCursorPos(&mouse);

        static POINT prevMouse = { mouse.x, mouse.y };

        // Calculate mouse movement delta
        float deltaX = (mouse.x - prevMouse.x) * 0.25f;
        float deltaY = (mouse.y - prevMouse.y) * 0.25f;

        m_camOrientation.y -= deltaX; 
        m_camOrientation.x -= deltaY; 

     
        prevMouse = mouse;
    }

    // Calculate new look direction from rotation
   /* m_camLookDirection.x = sin(m_camOrientation.y * 3.1415f / 180);
    m_camLookDirection.z = cos(m_camOrientation.y * 3.1415f / 180);
    m_camLookDirection.Normalize();*/

    //Create look direction for mouse
    float pitch = DirectX::XMConvertToRadians(m_camOrientation.x);
    float yaw = DirectX::XMConvertToRadians(m_camOrientation.y);

    m_camLookDirection.x = cos(pitch) * sin(yaw);
    m_camLookDirection.y = sin(pitch);
    m_camLookDirection.z = cos(pitch) * cos(yaw);
    m_camLookDirection.Normalize();

    // Create right vector from look direction
    m_camLookDirection.Cross(DirectX::SimpleMath::Vector3::UnitY, m_camRight);

    if (forward)
    {
        m_camPosition += m_camLookDirection * m_movespeed;
    }
    if (back)
    {
        m_camPosition -= m_camLookDirection * m_movespeed;
    }
    if (right)
    {
        m_camPosition += m_camRight * m_movespeed;
    }
    if (left)
    {
        m_camPosition -= m_camRight * m_movespeed;
    }
    // Update look-at point
    m_camLookAt = m_camPosition + m_camLookDirection;
}

void Camera::CreateArcball(float deltaTime)
{
    // Hardcoded values for now
    static float radius = 6.0f;
    static float speed = 0.5f;
    static float theta = 0.0f;
    const float phi = 0.3f;  // vertical angle
    static float pitch = 20.0f;  // Degrees

    // Target to orbit around (origin for now)
    DirectX::SimpleMath::Vector3 target = arcballTarget;

    // Auto-rotate
    theta += speed * deltaTime;

    // Convert spherical to Cartesian
    float x = radius * cosf(phi) * sinf(theta);
    float y = radius * sinf(phi);
    float z = radius * cosf(phi) * cosf(theta);

    // Calculate new position
    m_camPosition = target + DirectX::SimpleMath::Vector3(x, y, z);

    // Calculate direction to target
    DirectX::SimpleMath::Vector3 direction = target - m_camPosition;

    // Get yaw from direction
    float yaw = atan2(direction.x, direction.z);

    // Convert pitch and yaw to radians
    float pitchRad = DirectX::XMConvertToRadians(pitch);
    float yawRad = yaw;

    // Update orientation vector
    m_camOrientation.x = pitch;
    m_camOrientation.y = DirectX::XMConvertToDegrees(yawRad);

    // Calculate look direction
    m_camLookDirection.x = cos(pitchRad) * sin(yawRad);
    m_camLookDirection.y = sin(pitchRad);
    m_camLookDirection.z = cos(pitchRad) * cos(yawRad);
    m_camLookDirection.Normalize();

    // Update look-at point
    m_camLookAt = m_camPosition + m_camLookDirection;

    // Update right vector
    m_camLookDirection.Cross(DirectX::SimpleMath::Vector3::UnitY, m_camRight);
}

DirectX::SimpleMath::Vector3 Camera::GetForwardVector()
{
    return m_camLookDirection;
}

DirectX::SimpleMath::Vector3 Camera::GetRightVector()
{
    return m_camRight;
}


DirectX::SimpleMath::Matrix Camera::GetViewMatrix() const
{
    return DirectX::SimpleMath::Matrix::CreateLookAt(m_camPosition, m_camLookAt, DirectX::SimpleMath::Vector3::UnitY);
}
