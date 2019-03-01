#include "Camera.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <vendor/glm/gtc/quaternion.hpp>
#include <vendor/glm/gtx/norm.hpp>
#include <vendor/glm/gtc/matrix_transform.hpp>

namespace ShaderGraph
{
    Camera::Camera(glm::vec3 position, glm::vec3 up, glm::vec3 look, float zoom) :
            m_position(position),
            m_front(look-position),
            m_up(up),
            m_zoom(zoom)
    {

    }

    Camera::~Camera()
    {

    }

    glm::mat4 Camera::viewMatrix() const
    {
        return glm::lookAt(m_position, m_position + m_front, m_up);
    }

    void Camera::processMouseClick(int button, float xpos, float ypos) {
        m_mouseButton = button;
        m_mouseStartX = xpos;
        m_mouseStartY = ypos;
    }

    void Camera::processMouseMovement(int, float, float, bool)
    {

    }

    void Camera::processMouseScroll(float)
    {

    }

    float& Camera::zoom()
    {
        return m_zoom;
    }

    glm::vec3& Camera::position()
    {
        return m_position;
    }

    void Camera::setViewport(glm::vec4 viewport)
    {
        m_viewport = viewport;
    }

/*------------------------------------------------------------------------------------------------------------------------*/
/*                                            Trackball Camera                                                            */
/*------------------------------------------------------------------------------------------------------------------------*/


TrackballCamera::TrackballCamera(glm::vec3 position, glm::vec3 up, glm::vec3 center):
        Camera(position, glm::normalize(up), center, ZOOM),
        m_movementSpeed(1.0f),
        m_mouseSensitivity(1.0)
{
    m_radius  = glm::length(m_front);
    m_front  *= 1.f / m_radius;
}

TrackballCamera::~TrackballCamera()
{

}

void TrackballCamera::processMouseClick(int button, float xpos, float ypos)
{
    Camera::processMouseClick(button, xpos, ypos);

    switch (m_mouseButton)
    {
        case 0:
            // rotate
            m_rotStart = getMouseProjectionOnBall(xpos, ypos);
            m_rotEnd   = m_rotStart;
            break;

        case 1:
            // pan
            m_panStart = getMouseOnScreen(xpos, ypos);
            m_panEnd   = m_panStart;
            break;

        case 2:
            // zoom
            break;

        default:
            break;
    }
}

void TrackballCamera::processMouseMovement(int button, float xpos, float ypos, bool constrainPitch)
{
    // shutdown warning
    (void)button;
    (void)constrainPitch;

    switch (m_mouseButton)
    {
        case 0:
            // rotate
            m_rotEnd = getMouseProjectionOnBall(xpos, ypos);
            rotateCamera();
            break;

        case 1:
            // pan
            m_panEnd = getMouseOnScreen(xpos, ypos);
            panCamera();
            break;

        case 2:
            // zoom
            break;

        default:
            break;
    }
}

void TrackballCamera::processMouseScroll(float yoffset)
{
    (void) yoffset;
}


#define SQRT1_2  0.7071067811865476

glm::vec3 TrackballCamera::getMouseProjectionOnBall(float xpos, float ypos)
{
    glm::vec3 mouseOnBall = glm::vec3(
            (xpos - m_viewport.z * 0.5f) / (m_viewport.z * 0.5f),
            (m_viewport.w * 0.5f - ypos) / (m_viewport.w * 0.5f),
            0.0f);

    float length = glm::length(mouseOnBall);

    length = (length < 1.0f) ? length : 1.0f;

    mouseOnBall.z = std::sqrt(1 - length * length);
    mouseOnBall   = glm::normalize(mouseOnBall);

    return mouseOnBall;
}

glm::vec2 TrackballCamera::getMouseOnScreen(float xpos, float ypos)
{
    return glm::vec2(
            (xpos - m_viewport.z * 0.5f) / (m_viewport.z * 0.5f),
            (ypos - m_viewport.w * 0.5f) / (m_viewport.w * 0.5f));
}

void TrackballCamera::rotateCamera()
{
    glm::vec3 direction = m_rotEnd - m_rotStart;
    float velocity      = glm::length(direction);

    if (velocity > 0.0001)
    {
        glm::vec3 axis = glm::cross(m_rotEnd, m_rotStart);
        float length = glm::length(axis);
        axis = glm::normalize(axis);

        float angle = std::atan2(length, glm::dot(m_rotStart, m_rotEnd));

        glm::quat quaternion = glm::angleAxis(angle, axis);

        glm::vec3 center = m_position + m_front * m_radius;
        m_front          = glm::normalize(glm::rotate(quaternion, m_front));
        m_up             = glm::normalize(glm::rotate(quaternion , m_up));
        m_position       = center - m_front * m_radius;
        m_rotStart = m_rotEnd;
    }
}

void TrackballCamera::panCamera()
{
    glm::vec2 mov = m_panEnd - m_panStart;

    if (glm::length(mov) != 0.0f)
    {
        mov             *= m_mouseSensitivity * m_movementSpeed;
        glm::vec3 pan    = glm::cross(m_up, m_front) * mov.x + m_up * mov.y;
        m_position      += pan;
        m_panStart       = m_panEnd;
    }
}
}


