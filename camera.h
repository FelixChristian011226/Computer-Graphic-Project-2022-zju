#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 3.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }
    int inroom_1(glm::vec3 point_loc,int openflag, int in_it) {
        if (openflag != 1&&!in_it) {
            if (point_loc.x<11.7 && point_loc.x>-5.7 && point_loc.z > -13.2 && point_loc.z < 12.2)
                return 1;
        }
        else if(openflag == 1 && !in_it) {
            if ((point_loc.z>=12.2&&point_loc.z<13.2&&point_loc.x<10.7&&point_loc.x>9.3) || point_loc.x<11.7 && point_loc.x>-5.7 && point_loc.z > -13.2 && point_loc.z < 12.2)
                return 1;
        }
        else {
            if ((point_loc.z >= 12.7 && point_loc.z < 13.2 && point_loc.x < 10.7 && point_loc.x>9.3))
                return 1;
        }
        return 0;
    }
    int inroom_2(glm::vec3 point_loc, int openflag, int in_it) {

        if (openflag != 1 && !in_it) {
            if (((point_loc.x< 11.7 && point_loc.x> -5.7 && point_loc.z >  10.9 && point_loc.z < 12.2) ||
                (point_loc.x< 11.7 && point_loc.x>  10.4 && point_loc.z > -13.2 && point_loc.z < 12.2) || 
                (point_loc.x< -4.4 && point_loc.x> -5.7 && point_loc.z > -13.2 && point_loc.z < 12.2) || 
                (point_loc.x< 11.7 && point_loc.x> -5.7 && point_loc.z > -13.2 && point_loc.z < -11.9)||
                (point_loc.x< -2.4 && point_loc.x> -4.4 && point_loc.z > -11.9 && point_loc.z < -9.9))&&
                !(point_loc.x< -4.4 && point_loc.x> -5.7 && point_loc.z > -13.2 && point_loc.z < -11.7))
                return 1;
        }
        else if (openflag == 1 && !in_it) {
            if (((point_loc.z >= 12.2 && point_loc.z < 13.2 && point_loc.x < 10.7 && point_loc.x>9.3) || 
                (point_loc.x< 11.7 && point_loc.x> -5.7 && point_loc.z > 10.9 && point_loc.z < 12.2) ||
                (point_loc.x < 11.7 && point_loc.x> 10.4 && point_loc.z > -13.2 && point_loc.z < 12.2) ||
                (point_loc.x< -4.4 && point_loc.x> -5.7 && point_loc.z > -13.2 && point_loc.z < 12.2) ||
                (point_loc.x< 11.7 && point_loc.x> -5.7 && point_loc.z > -13.2 && point_loc.z < -11.9)||
                (point_loc.x< -2.4 && point_loc.x> -4.4 && point_loc.z > -11.9 && point_loc.z < -9.9)) &&
                !(point_loc.x< -4.4 && point_loc.x> -5.7 && point_loc.z > -13.2 && point_loc.z < -11.7))
                return 1;
        }
        else {
            if ((point_loc.z >= 12.7 && point_loc.z < 13.2 && point_loc.x < 10.7 && point_loc.x>9.3))
                return 1;
        }
        return 0;
    }
    int in_lift(glm::vec3 point_loc, int openflag) {
        if ((point_loc.z >= 12.7 && point_loc.z < 13.2 && point_loc.x < 10.7 && point_loc.x>9.3) || (point_loc.x<11.7 && point_loc.x>-0.7 && point_loc.z > -0.2 && point_loc.z < 12.2))
                return 1;
        return 0;
    }
    void ProcessKeyboard(Camera_Movement direction, float deltaTime, float current, int openflag, int floor, int in_it, int initemx, int initemz, int viewtype, float speed)
    {
        float velocity = speed * deltaTime;
        if (direction == FORWARD) {
            if (inroom_1(Position, openflag, in_it)&&floor==1 && viewtype==1) {
                if(!initemx && inroom_1(glm::vec3(Position.x+ Front.x * velocity, Position.y, Position.z),openflag, in_it))
                Position.x += Front.x * velocity;
                if (!initemz && inroom_1(glm::vec3(Position.x, Position.y, Position.z+Front.z * velocity), openflag, in_it))
                Position.z += Front.z * velocity;
                if (Position.y + Front.y * velocity < 0.0) {
                    Position.y = current;
                }
            }
            if (floor == 0 && viewtype == 1) {
                if (!initemx && in_lift(glm::vec3(Position.x + Front.x * velocity, Position.y, Position.z), openflag))
                    Position.x += Front.x * velocity;
                if (!initemz && in_lift(glm::vec3(Position.x, Position.y, Position.z + Front.z * velocity), openflag))
                    Position.z += Front.z * velocity;
                if (Position.y + Front.y * velocity < 0.0) {
                    Position.y = current;
                }
            }
            if (inroom_2(Position, openflag, in_it) && floor == 2 && viewtype == 1) {
                if (inroom_2(glm::vec3(Position.x + Front.x * velocity, Position.y, Position.z), openflag, in_it))
                    Position.x += Front.x * velocity;
                if (inroom_2(glm::vec3(Position.x, Position.y, Position.z + Front.z * velocity), openflag, in_it))
                    Position.z += Front.z * velocity;
                if (Position.y + Front.y * velocity < 0.0) {
                    Position.y = current;
                }
            }
            if (viewtype == 0) {
                Position += Front * velocity;
            }
        }
            
        if (direction == BACKWARD) {
            if (inroom_1(Position, openflag, in_it) && floor == 1 && viewtype == 1) {
                if (!initemx && inroom_1(glm::vec3(Position.x - Front.x * velocity, Position.y, Position.z), openflag, in_it))
                    Position.x -= Front.x * velocity;
                if (!initemz && inroom_1(glm::vec3(Position.x, Position.y, Position.z - Front.z * velocity), openflag, in_it))
                    Position.z -= Front.z * velocity;
                if (Position.y + Front.y * velocity < 0.0) {
                    Position.y = current;
                }
            }
            if (floor == 0 && viewtype == 1) {
                if (!initemx && in_lift(glm::vec3(Position.x - Front.x * velocity, Position.y, Position.z), openflag))
                    Position.x -= Front.x * velocity;
                if (!initemz && in_lift(glm::vec3(Position.x, Position.y, Position.z - Front.z * velocity), openflag))
                    Position.z -= Front.z * velocity;
                if (Position.y + Front.y * velocity < 0.0) {
                    Position.y = current;
                }
            }
            if (inroom_2(Position, openflag, in_it) && floor == 2 && viewtype == 1) {
                if (inroom_2(glm::vec3(Position.x - Front.x * velocity, Position.y, Position.z), openflag, in_it))
                    Position.x -= Front.x * velocity;
                if (inroom_2(glm::vec3(Position.x, Position.y, Position.z - Front.z * velocity), openflag, in_it))
                    Position.z -= Front.z * velocity;
                if (Position.y + Front.y * velocity < 0.0) {
                    Position.y = current;
                }
            }
            if (viewtype == 0) {
                Position -= Front * velocity;
            }
        }
        if (direction == LEFT) {
            if (inroom_1(Position, openflag, in_it) && floor == 1 && viewtype == 1) {
                if (!initemx && inroom_1(glm::vec3(Position.x - Right.x * velocity, Position.y, Position.z), openflag, in_it))
                    Position.x -= Right.x * velocity;
                if (!initemz && inroom_1(glm::vec3(Position.x, Position.y, Position.z - Right.z * velocity), openflag, in_it))
                    Position.z -= Right.z * velocity;
                if (Position.y + Right.y * velocity < 0.0) {
                    Position.y = current;
                }
            }
            if (floor == 0 && viewtype == 1) {
                if (!initemx && in_lift(glm::vec3(Position.x - Right.x * velocity, Position.y, Position.z), openflag))
                    Position.x -= Right.x * velocity;
                if (!initemz && in_lift(glm::vec3(Position.x, Position.y, Position.z - Right.z * velocity), openflag))
                    Position.z -= Right.z * velocity;
                if (Position.y + Right.y * velocity < 0.0) {
                    Position.y = current;
                }
            }
            if (inroom_2(Position, openflag, in_it) && floor == 2 && viewtype == 1) {
                if (inroom_2(glm::vec3(Position.x - Right.x * velocity, Position.y, Position.z), openflag, in_it))
                    Position.x -= Right.x * velocity;
                if (inroom_2(glm::vec3(Position.x, Position.y, Position.z - Right.z * velocity), openflag, in_it))
                    Position.z -= Right.z * velocity;
                if (Position.y + Right.y * velocity < 0.0) {
                    Position.y = current;
                }
            }
            if (viewtype == 0) {
                Position -= Right * velocity;
            }
        }
        if (direction == RIGHT) {
            if (inroom_1(Position, openflag, in_it) && floor == 1 && viewtype == 1) {
                if (!initemx && inroom_1(glm::vec3(Position.x + Right.x * velocity, Position.y, Position.z), openflag, in_it))
                    Position.x += Right.x * velocity;
                if (!initemz && inroom_1(glm::vec3(Position.x, Position.y, Position.z + Right.z * velocity), openflag, in_it))
                    Position.z += Right.z * velocity;
                if (Position.y + Right.y * velocity < 0.0) {
                    Position.y = current;
                }
            }
            if (floor == 0 && viewtype == 1) {
                if (!initemx && in_lift(glm::vec3(Position.x + Right.x * velocity, Position.y, Position.z), openflag))
                    Position.x += Right.x * velocity;
                if (!initemz && in_lift(glm::vec3(Position.x, Position.y, Position.z + Right.z * velocity), openflag))
                    Position.z += Right.z * velocity;
                if (Position.y + Right.y * velocity < 0.0) {
                    Position.y = current;
                }
            }
            if (inroom_2(Position, openflag, in_it) && floor == 2 && viewtype == 1) {
                if (inroom_2(glm::vec3(Position.x + Right.x * velocity, Position.y, Position.z), openflag, in_it))
                    Position.x += Right.x * velocity;
                if (inroom_2(glm::vec3(Position.x, Position.y, Position.z + Right.z * velocity), openflag, in_it))
                    Position.z += Right.z * velocity;
                if (Position.y + Right.y * velocity < 0.0) {
                    Position.y = current;
                }
            }
            if (viewtype == 0) {
                Position += Right * velocity;
            }
        }
    }
    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));
    }
};
#endif