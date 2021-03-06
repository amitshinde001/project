#pragma once

#include <Renderer.h>
#include <gl\GL.h>
#include <gl\GLU.h>

namespace Features
{
    using namespace Interfaces;

    // Sample renderer to render multi-color pyramid as part of SCENE_TYPE_TEST0 scene
    class TestRenderer : public IRenderer
    {
    public:
        /// Method for retrieving name of the renderer
        /// @param rendererName buffer to be filled with the renderer name
        /// @return RENDERER_RESULT_SUCCESS if succeded, rendererName to contain null-terminated name
        ///         RENDERER_RESULT_ERROR if failed, renderName is ignored
        const char* GetName() override
        {
            static const char name[] = "TestRenderer";
            return name;
        }

        /// Method for performing one-time renderer initialization.
        /// Renderer can initialize global/static instances as part of this method
        /// @param window identifier of the window where drawing is directed
        /// @return RENDERER_RESULT_SUCCESS if succeded
        ///         RENDERER_RESULT_ERROR if failed.
        RendererResult Initialize(Window window) override
        {
            return RENDERER_RESULT_SUCCESS;
        }

        /// Method for performing one-time renderer un-initialization before it is unloaded
        /// Renderer can perform global cleanup as part of this method
        void Uninitialize(void) override
        {
        }

        /// Method for performing scene-specific initialization
        /// This method will be called by the host before rendering a scene to the active renderer.
        /// Renderer should do initialization of scene specific things as part of this method
        /// @param scene Identifier of a scene to be initialized
        /// @return RENDERER_RESULT_SUCCESS if succeded
        ///         RENDERER_RESULT_ERROR if failed.
        RendererResult InitializeScene(SceneType scene) override
        {
            return RENDERER_RESULT_SUCCESS;
        }

        /// Method for performing scene-specific initialization
        /// This method will be called by the host after rendering a scene to the active renderer
        /// Renderer should do cleanup of scene specific things done as part of scene initialize.
        /// @param scene Identifier of a scene to be cleaned-up
        void UninitializeScene(SceneType scene) override
        {
        }

        /// Method for rendering a frame in a scene
        /// This method will be called by the host per frame of a scene only to the active renderer
        /// @param params describes the parameters curresponding to this render
        /// @return RENDERER_RESULT_SUCCESS if succeded in building the frame
        ///         RENDERER_RESULT_ERROR if failed in building the frame
        ///         RENDERER_RESULT_FINISHED if renderer has finished building its last frame of the scene.
        ///                                   in such cases no further frame calls would be made for this scene
        ///                                   to the renderer.
        virtual RendererResult Render(const RenderParams &params) override
        {
            static unsigned renderFrameCount = 1000;
            RendererResult result = RENDERER_RESULT_FINISHED;

            // render 1000 frames before transitioning to next scene
            if (params.scene == SCENE_TYPE_TEST0 && --renderFrameCount > 0)
            {
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();

                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

                glTranslatef(0.0f, 0.0f, -6.0f);
                glRotatef(0.1f * params.frameIdFromSceneStart, 0.0f, 1.0f, 0.0f);

                GLfloat pyramidVertices[][3] = {
                    // front
                    { 0.0f, 1.0f, 0.0f },
                    { -1.0f, -1.0f, 1.0f },
                    { 1.0f, -1.0f, 1.0f },

                    // left
                    { 0.0f, 1.0f, 0.0f },
                    { -1.0f, -1.0f, -1.0f },
                    { -1.0f, -1.0f, 1.0f },

                    //back
                    { 0.0f, 1.0f, 0.0f },
                    { -1.0f, -1.0f, -1.0f },
                    { 1.0f, -1.0f, -1.0f },

                    // right
                    { 0.0f, 1.0f, 0.0f },
                    { 1.0f, -1.0f, 1.0f },
                    { 1.0f, -1.0f, -1.0f },
                };

                // Draw triangles for the pyramid
                glBegin(GL_TRIANGLES);
                    glColor3f(1.0f, 0.0f, 0.0f);
                    glNormal3f(0.0f, 0.447214f, 0.894427f);
                    glVertex3fv((GLfloat*)&pyramidVertices[0]);
                    glVertex3fv((GLfloat*)&pyramidVertices[1]);
                    glVertex3fv((GLfloat*)&pyramidVertices[2]);

                    glColor3f(0.0f, 1.0f, 0.0f);
                    glNormal3f(-0.894427f, 0.447214f, 0.0f);
                    glVertex3fv((GLfloat*)&pyramidVertices[3]);
                    glVertex3fv((GLfloat*)&pyramidVertices[4]);
                    glVertex3fv((GLfloat*)&pyramidVertices[5]);

                    glColor3f(0.0f, 0.0f, 1.0f);
                    glNormal3f(0.0f, 0.447214f, -0.894427f);
                    glVertex3fv((GLfloat*)&pyramidVertices[6]);
                    glVertex3fv((GLfloat*)&pyramidVertices[7]);
                    glVertex3fv((GLfloat*)&pyramidVertices[8]);

                    glColor3f(0.0f, 1.0f, 1.0f);
                    glNormal3f(0.894427f, 0.447214f, 0.0f);
                    glVertex3fv((GLfloat*)&pyramidVertices[9]);
                    glVertex3fv((GLfloat*)&pyramidVertices[10]);
                    glVertex3fv((GLfloat*)&pyramidVertices[11]);
                glEnd();

                result = RENDERER_RESULT_SUCCESS;
            }
            return result;
        }

        /// Generic method to notify active renderer about a message posted to host window. The message can be
        /// from system or initiated by the host itself.
        /// @param message OS dependent structure that describes the system message being processed.
        void OnMessage(const Message &message) override
        {
        }

        /// Generic method to notify active renderer about the change in the dimensions of the host window
        /// @param width New width of the window
        /// @param height New height of the window
        void OnResize(unsigned int width, unsigned int height) override
        {
            // select projection matrix
            glMatrixMode(GL_PROJECTION);
            // reset projection matrix
            glLoadIdentity();
            // calculate the aspect ratio of the view
            gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
        }
    };

    // Sample renderer to render multi-color pyramid as part of SCENE_TYPE_TEST0 scene
    class TestRenderer1 : public IRenderer
    {
    public:
        /// Method for retrieving name of the renderer
        /// @param rendererName buffer to be filled with the renderer name
        /// @return RENDERER_RESULT_SUCCESS if succeded, rendererName to contain null-terminated name
        ///         RENDERER_RESULT_ERROR if failed, renderName is ignored
        const char* GetName() override
        {
            static const char name[] = "TestRenderer1";
            return name;
        }

        /// Method for performing one-time renderer initialization.
        /// Renderer can initialize global/static instances as part of this method
        /// @param window identifier of the window where drawing is directed
        /// @return RENDERER_RESULT_SUCCESS if succeded
        ///         RENDERER_RESULT_ERROR if failed.
        RendererResult Initialize(Window window) override
        {
            return RENDERER_RESULT_SUCCESS;
        }

        /// Method for performing one-time renderer un-initialization before it is unloaded
        /// Renderer can perform global cleanup as part of this method
        void Uninitialize(void) override
        {
        }

        /// Method for performing scene-specific initialization
        /// This method will be called by the host before rendering a scene to the active renderer.
        /// Renderer should do initialization of scene specific things as part of this method
        /// @param scene Identifier of a scene to be initialized
        /// @return RENDERER_RESULT_SUCCESS if succeded
        ///         RENDERER_RESULT_ERROR if failed.
        RendererResult InitializeScene(SceneType scene) override
        {
            return RENDERER_RESULT_SUCCESS;
        }

        /// Method for performing scene-specific initialization
        /// This method will be called by the host after rendering a scene to the active renderer
        /// Renderer should do cleanup of scene specific things done as part of scene initialize.
        /// @param scene Identifier of a scene to be cleaned-up
        void UninitializeScene(SceneType scene) override
        {
        }

        /// Method for rendering a frame in a scene
        /// This method will be called by the host per frame of a scene only to the active renderer
        /// @param params describes the parameters curresponding to this render
        /// @return RENDERER_RESULT_SUCCESS if succeded in building the frame
        ///         RENDERER_RESULT_ERROR if failed in building the frame
        ///         RENDERER_RESULT_FINISHED if renderer has finished building its last frame of the scene.
        ///                                   in such cases no further frame calls would be made for this scene
        ///                                   to the renderer.
        virtual RendererResult Render(const RenderParams &params) override
        {
            static unsigned renderFrameCount = 1000;
            RendererResult result = RENDERER_RESULT_FINISHED;

            // render 1000 frames before transitioning to next scene
            if (params.scene == SCENE_TYPE_TEST0 && --renderFrameCount > 0)
            {
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

                glTranslatef(0.0f, 0.0f, -6.0f);
                glRotatef(-0.1f * params.frameIdFromSceneStart, 0.0f, 1.0f, 0.0f);

                GLfloat pyramidVertices[][3] = {
                    // front
                    { 0.0f, 1.0f, 0.0f },
                    { -1.0f, -1.0f, 1.0f },
                    { 1.0f, -1.0f, 1.0f },

                    // left
                    { 0.0f, 1.0f, 0.0f },
                    { -1.0f, -1.0f, -1.0f },
                    { -1.0f, -1.0f, 1.0f },

                    //back
                    { 0.0f, 1.0f, 0.0f },
                    { -1.0f, -1.0f, -1.0f },
                    { 1.0f, -1.0f, -1.0f },

                    // right
                    { 0.0f, 1.0f, 0.0f },
                    { 1.0f, -1.0f, 1.0f },
                    { 1.0f, -1.0f, -1.0f },
                };

                // Draw triangles for the pyramid
                glBegin(GL_TRIANGLES);
                glColor3f(1.0f, 0.0f, 0.0f);
                glNormal3f(0.0f, 0.447214f, 0.894427f);
                glVertex3fv((GLfloat*)&pyramidVertices[0]);
                glVertex3fv((GLfloat*)&pyramidVertices[1]);
                glVertex3fv((GLfloat*)&pyramidVertices[2]);

                glColor3f(0.0f, 1.0f, 0.0f);
                glNormal3f(-0.894427f, 0.447214f, 0.0f);
                glVertex3fv((GLfloat*)&pyramidVertices[3]);
                glVertex3fv((GLfloat*)&pyramidVertices[4]);
                glVertex3fv((GLfloat*)&pyramidVertices[5]);

                glColor3f(0.0f, 0.0f, 1.0f);
                glNormal3f(0.0f, 0.447214f, -0.894427f);
                glVertex3fv((GLfloat*)&pyramidVertices[6]);
                glVertex3fv((GLfloat*)&pyramidVertices[7]);
                glVertex3fv((GLfloat*)&pyramidVertices[8]);

                glColor3f(0.0f, 1.0f, 1.0f);
                glNormal3f(0.894427f, 0.447214f, 0.0f);
                glVertex3fv((GLfloat*)&pyramidVertices[9]);
                glVertex3fv((GLfloat*)&pyramidVertices[10]);
                glVertex3fv((GLfloat*)&pyramidVertices[11]);
                glEnd();

                result = RENDERER_RESULT_SUCCESS;
            }
            return result;
        }

        /// Generic method to notify active renderer about a message posted to host window. The message can be
        /// from system or initiated by the host itself.
        /// @param message OS dependent structure that describes the system message being processed.
        void OnMessage(const Message &message) override
        {
        }

        /// Generic method to notify active renderer about the change in the dimensions of the host window
        /// @param width New width of the window
        /// @param height New height of the window
        void OnResize(unsigned int width, unsigned int height) override
        {
            // select projection matrix
            glMatrixMode(GL_PROJECTION);
            // reset projection matrix
            glLoadIdentity();
            // calculate the aspect ratio of the view
            gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
        }
    };

    // Sample renderer to render yellow colored pyramid as part of SCENE_TYPE_TEST1 scene
    class TestRenderer2 : public IRenderer
    {
    public:
        /// Method for retrieving name of the renderer
        /// @param rendererName buffer to be filled with the renderer name
        /// @return RENDERER_RESULT_SUCCESS if succeded, rendererName to contain null-terminated name
        ///         RENDERER_RESULT_ERROR if failed, renderName is ignored
        const char* GetName() override
        {
            static const char name[] = "TestRenderer2";
            return name;
        }

        /// Method for performing one-time renderer initialization.
        /// Renderer can initialize global/static instances as part of this method
        /// @param window identifier of the window where drawing is directed
        /// @return RENDERER_RESULT_SUCCESS if succeded
        ///         RENDERER_RESULT_ERROR if failed.
        RendererResult Initialize(Window window) override
        {
            return RENDERER_RESULT_SUCCESS;
        }

        /// Method for performing one-time renderer un-initialization before it is unloaded
        /// Renderer can perform global cleanup as part of this method
        void Uninitialize(void) override
        {
        }

        /// Method for performing scene-specific initialization
        /// This method will be called by the host before rendering a scene to the active renderer.
        /// Renderer should do initialization of scene specific things as part of this method
        /// @param scene Identifier of a scene to be initialized
        /// @return RENDERER_RESULT_SUCCESS if succeded
        ///         RENDERER_RESULT_ERROR if failed.
        RendererResult InitializeScene(SceneType scene) override
        {
            return RENDERER_RESULT_SUCCESS;
        }

        /// Method for performing scene-specific initialization
        /// This method will be called by the host after rendering a scene to the active renderer
        /// Renderer should do cleanup of scene specific things done as part of scene initialize.
        /// @param scene Identifier of a scene to be cleaned-up
        void UninitializeScene(SceneType scene) override
        {
        }

        /// Method for rendering a frame in a scene
        /// This method will be called by the host per frame of a scene only to the active renderer
        /// @param params describes the parameters curresponding to this render
        /// @return RENDERER_RESULT_SUCCESS if succeded in building the frame
        ///         RENDERER_RESULT_ERROR if failed in building the frame
        ///         RENDERER_RESULT_FINISHED if renderer has finished building its last frame of the scene.
        ///                                   in such cases no further frame calls would be made for this scene
        ///                                   to the renderer.
        virtual RendererResult Render(const RenderParams &params) override
        {
            RendererResult result = RENDERER_RESULT_FINISHED;

            // render for 5 secs before transitioning to next scene
            if (params.scene == SCENE_TYPE_TEST1 && params.elapsedFromSceneStart < 5 * 1000 * 1000)
            {
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

                glTranslatef(0.0f, 0.0f, -6.0f);
                glRotatef(0.1f * params.frameIdFromSceneStart, 0.0f, 1.0f, 0.0f);

                GLfloat pyramidVertices[][3] = {
                    // front
                    { 0.0f, 1.0f, 0.0f },
                    { -1.0f, -1.0f, 1.0f },
                    { 1.0f, -1.0f, 1.0f },

                    // left
                    { 0.0f, 1.0f, 0.0f },
                    { -1.0f, -1.0f, -1.0f },
                    { -1.0f, -1.0f, 1.0f },

                    //back
                    { 0.0f, 1.0f, 0.0f },
                    { -1.0f, -1.0f, -1.0f },
                    { 1.0f, -1.0f, -1.0f },

                    // right
                    { 0.0f, 1.0f, 0.0f },
                    { 1.0f, -1.0f, 1.0f },
                    { 1.0f, -1.0f, -1.0f },
                };

                // Draw yellow triangles for the pyramid
                glColor3f(1.0f, 1.0f, 0.0f);

                glBegin(GL_TRIANGLES);
                glNormal3f(0.0f, 0.447214f, 0.894427f);
                glVertex3fv((GLfloat*)&pyramidVertices[0]);
                glVertex3fv((GLfloat*)&pyramidVertices[1]);
                glVertex3fv((GLfloat*)&pyramidVertices[2]);

                glNormal3f(-0.894427f, 0.447214f, 0.0f);
                glVertex3fv((GLfloat*)&pyramidVertices[3]);
                glVertex3fv((GLfloat*)&pyramidVertices[4]);
                glVertex3fv((GLfloat*)&pyramidVertices[5]);

                glNormal3f(0.0f, 0.447214f, -0.894427f);
                glVertex3fv((GLfloat*)&pyramidVertices[6]);
                glVertex3fv((GLfloat*)&pyramidVertices[7]);
                glVertex3fv((GLfloat*)&pyramidVertices[8]);

                glNormal3f(0.894427f, 0.447214f, 0.0f);
                glVertex3fv((GLfloat*)&pyramidVertices[9]);
                glVertex3fv((GLfloat*)&pyramidVertices[10]);
                glVertex3fv((GLfloat*)&pyramidVertices[11]);
                glEnd();

                result = RENDERER_RESULT_SUCCESS;
            }
            return result;
        }

        /// Generic method to notify active renderer about a message posted to host window. The message can be
        /// from system or initiated by the host itself.
        /// @param message OS dependent structure that describes the system message being processed.
        void OnMessage(const Message &message) override
        {
        }

        /// Generic method to notify active renderer about the change in the dimensions of the host window
        /// @param width New width of the window
        /// @param height New height of the window
        void OnResize(unsigned int width, unsigned int height) override
        {
            // select projection matrix
            glMatrixMode(GL_PROJECTION);
            // reset projection matrix
            glLoadIdentity();
            // calculate the aspect ratio of the view
            gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
        }
    };

}
