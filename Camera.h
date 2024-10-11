

#ifndef CAMERA_H
#define CAMERA_H


namespace PAG
{
    class Camera
    {
        private:
            static Camera* instancia;

        public:
            static Camera* GetInstancia ();

    };
}



#endif //CAMERA_H
