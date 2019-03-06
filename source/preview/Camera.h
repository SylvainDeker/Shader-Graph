#ifndef SHADERGRAPH_CAMERA_H
#define SHADERGRAPH_CAMERA_H

#include <core/Core.h>

namespace ShaderGraph
{
    /// Defines several possible options for camera movement.
    /// Used as abstraction to stay away from window-system specific input methods
    enum ECameraMovement {
        LEFT = 0,
        FORWARD,
        RIGHT,
        BACKWARD
    };

    /// Default camera values (from learnopenGL tutorial)
    constexpr float YAW        = -90.0f;
    constexpr float PITCH      =  0.0f;
    constexpr float SPEED      =  3.0f;
    constexpr float SENSITIVTY =  0.25f;
    constexpr float ZOOM       =  45.0f;


    /*------------------------------------------------------------------------------------------------------------------------*/
    /*                                                Abstract Camera                                                         */
    /*------------------------------------------------------------------------------------------------------------------------*/

    class Camera
    {

    public:
        Camera( glm::vec3 position  = glm::vec3(0.f, 0.f, 1.f),
                glm::vec3 up        = glm::vec3(0.f, 1.f, 0.f),
                glm::vec3 look      = glm::vec3(0.f, 0.f, 0.f),
                float zoom          = ZOOM );

        virtual ~Camera();

        /// @return : the view matrix calculated using Eular Angles and the LookAt Matrix
        glm::mat4 viewMatrix() const;

        float & zoom();
        glm::vec3 & position();

        void setViewport(glm::vec4 viewport);

        /// Processes input received from a mouse input system.
        virtual void processMouseClick(int button, float xpos, float ypos);

        /// Processes input received from a mouse input system.
        /// Expects the offset value in both the x and y direction.
        virtual void processMouseMovement(int button, float xpos, float ypos, bool constraint = true);

        /// Processes input received from a mouse scroll-wheel event.
        /// Only requires input on the vertical wheel-axis
        virtual void processMouseScroll(float yoffset);

    protected:
        glm::vec3 m_position;
        glm::vec3 m_front;
        glm::vec3 m_up;
        float     m_zoom;

        glm::vec4 m_viewport;

        int   m_mouseButton;
        float m_mouseStartX;
        float m_mouseStartY;
    };

    /*------------------------------------------------------------------------------------------------------------------------*/
    /*                                            Trackball Camera                                                            */
    /*------------------------------------------------------------------------------------------------------------------------*/

    class TrackballCamera : public Camera
    {
    public:
        TrackballCamera( glm::vec3 position = glm::vec3(0.0f, 0.0f,  0.0f),
                         glm::vec3 up       = glm::vec3(0.0f, 1.0f,  0.0f),
                         glm::vec3 center   = glm::vec3(0.0f, 0.0f, -1.0f) );

        ~TrackballCamera();

        /// Processes input received from a mouse input system.
        void processMouseClick(int button, float xpos, float ypos) override;

        /// Processes input received from a mouse input system.
        /// Expects the offset value in both the x and y direction.
        void processMouseMovement(int button, float xpos, float ypos, bool constrainPitch = true) override;

        /// Processes input received from a mouse scroll-wheel event.
        /// Only requires input on the vertical wheel-axis
        void processMouseScroll(float yoffset) override;

    private:
        /// Distance to center
        float m_radius;

        /* ==================================================================================== */
        /* Camera options */
        /* ==================================================================================== */
        float m_movementSpeed;
        float m_mouseSensitivity;

        /* ==================================================================================== */
        /* Rotation */
        /* ==================================================================================== */
        glm::vec3 m_rotStart;
        glm::vec3 m_rotEnd;

        void rotateCamera();

        /* ==================================================================================== */
        /* Pan */
        /* ==================================================================================== */
        glm::vec2 m_panStart;
        glm::vec2 m_panEnd;

        void panCamera();

        /* ==================================================================================== */
        /* Misc */
        /* ==================================================================================== */
        glm::vec3 getMouseProjectionOnBall(float xpos, float ypos);
        glm::vec2 getMouseOnScreen(float xpos, float ypos);
    };
}

#endif //SHADERGRAPH_CAMERA_H
