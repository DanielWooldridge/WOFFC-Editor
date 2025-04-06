#pragma once

#include <d3d11.h>
#include <SimpleMath.h>  

class Camera 
{
public:
    Camera();
    ~Camera();

    void Init();
    void Update(bool forward, bool back, bool left, bool right, bool rotLeft, bool rotRight, bool RB, POINT mouse, bool arcCamEnabled);
    void CreateArcball(float deltaTime);

    DirectX::SimpleMath::Vector3 GetForwardVector();
    DirectX::SimpleMath::Vector3 GetRightVector();


    DirectX::SimpleMath::Matrix GetViewMatrix() const;
    bool m_isArcballOn;
    DirectX::SimpleMath::Vector3 arcballTarget;

private:
    DirectX::SimpleMath::Vector3 m_camPosition;
    DirectX::SimpleMath::Vector3 m_camOrientation;
    DirectX::SimpleMath::Vector3 m_camLookAt;
    DirectX::SimpleMath::Vector3 m_camLookDirection;
    DirectX::SimpleMath::Vector3 m_camRight;
    float m_camRotRate;
    float m_movespeed;
   
    //POINT mouse;
};
