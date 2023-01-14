#include "head.h"
void inilight();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void LoadContainers();
void SaveContainers();
void SaveTransporters();
void LoadTransporters();
void SaveShelves();
void LoadShelves();
int judge_one_x(glm::vec3 pos, float[]);
int judge_one_z(glm::vec3 pos, float[]);
void initem(glm::vec3 pos, glm::vec3 pre_pos);
void judge_for_col(int &jx, int &jz);
void flush();
bool objinobj(Object* obj, int flag, int type);
bool relationship(float f1[], float f2[]);
bool inside_room(float pos[]);
bool nearlift();
time_t get_mtime(std::string filename);
void DrawUI();


std::vector<int> col_dector_x;
std::vector<int> col_dector_z;

std::vector<int> col_dector_x_pre;
std::vector<int> col_dector_z_pre;

int operation = 0;
const float x_corner = 0.5;
const float z_corner = 3.0;
const float x_distance = 7.0;
const float z_distance = 4.0;
const int lengthofshelf = 5;
const int row = 4;
const int col = 2;


const float container_distance = 1.0;
roof* Roof;
elift* Lift;
skybox* Skybox;
ground* Ground;
floors* Floor;
wall* Wall;
Forklift* forklift;
Container* container;
Shelf* shelf;
Transporter* transporter;
Railing* railing[6];
Console* console;
int container_num = 0;                              //
int shelf_num = 0;
int selected_index = -1;
int temp_index = -1;
int default_shelf_length = 3;
int default_transporter_length = 5;
int transporter_num = 0;
std::vector<glm::vec3> transporter_pos;
std::vector<glm::vec3> container_pos;
std::vector<glm::vec3> shelf_pos;

// settings
int lock = 0;
int viewtype = 1;
int in_it = 0;
int floor1 = 1;
float loc = 0;
float loc1 = 0;
float locy = 0;
int protect = 0;
int protect1 = 0;
int uprotect = 0;
int uprotect1 = 0;
int protect2 = 0;
int protect3 = 0;
int openflag = 0;
int openflag1 = 0;
int upflag = 0;
const unsigned int SCR_WIDTH = 2550;
const unsigned int SCR_HEIGHT = 1650;
const GLfloat  PI = 3.14159265358979323846f;
GLfloat angle = 0.0f;
GLfloat angle1 = 0.0f;
GLfloat t = 0.0;
GLfloat height = 0.0;
GLfloat  player_height= 0.0;
const int Y_SEGMENTS = 40;
const int X_SEGMENTS = 40;
glm::vec3 temp(0.0f);
bool control_panel = false;                  //
bool forklift_selected = false;
bool container_selected = false;
bool transporter_selected = false;
bool shelf_selected = false;
bool select_mode = false;
bool edit_mode = false;
// camera
Camera camera(glm::vec3(-0.5f, 1.3f, 0.0f));
glm::vec3 overview(-0.5f, 5.0f, 0.0f);
glm::vec3 firstview(-0.5f, 0.3f, 0.0f);
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool Jump_flag = false;
bool sight_flag = false;
bool run_flag = false;
bool stop_flag = false;
bool stop_flag1 = false;
bool flag1 = false;
bool count = false;
bool count1 = false;
bool speedup = false;
// timing
float Timeforsight = 0.0f;
float deltaTime = 0.0f;	
float lastFrame = 0.0f;

//speed
float c_speed = 5.0;

glm::vec3 pointLightPositions[20];
int main()
{
    glfwInit();
#if defined(IMGUI_IMPL_OPENGL_ES2)                                                                      //
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader box("shader/area.vs.txt", "shader/area.fs.txt");
    Shader lift("shader/area.vs.txt", "shader/area.fs.txt");
    Shader liftfork("shader/forklift.vs.txt", "shader/forklift.fs.txt");
    Shader line_shader("shader/line.vs.txt", "shader/line.fs.txt");
    Shader norm_shader("shader/forklift.vs.txt", "shader/forklift.fs.txt");

    

    //skybox defines
    Shader skyboxShader("shader/skybox.vs.txt", "shader/skybox.fs.txt");
    Skybox = new skybox(faces, skyboxVertices);
    Skybox->initial();
    //ground defines
    Shader area("shader/forklift.vs.txt", "shader/forklift.fs.txt");
    Ground = new ground("pic/R-C.jpg", vertices, indices);
    Ground->initial();

    //floor defines
    Shader area_back("shader/area.vs.txt", "shader/area.fs.txt");
    Floor = new floors("pic/up.jpg", vertices1, indices);
    Floor->initial();

    //wall defines
    Wall = new wall("pic/wall.jpg", bvertices);
    Wall->initial();

    //lift defines
    Lift = new elift("pic/up.jpg", bvertices);
    Lift->initial();

    //roof defines
    Roof = new roof("pic/up.jpg", rvertices);
    Roof->initial();



    //点光源
    inilight();
    
    //叉车
    forklift = new Forklift(10.0, 10.0, 180);

    //传送带
    //transporter = new Transporter(0.0, -5.0, 5);

    //架子
    /*for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            shelf = new Shelf(x_corner + x_distance * j, z_corner + z_distance * i, true, 3);
        }
    }*/

    //栏杆
    for (int i = 0; i < 6; i++) {
        if (i == 0)railing[i] = new Railing(-4.15, 4.01, 10.25, 0, 20);
        if (i == 1)railing[i] = new Railing(10.1, 4.01, 10.35, 0, 22);
        if (i == 2)railing[i] = new Railing(-3.7, 4.01, 10.6, 1, 14);
        if (i == 3)railing[i] = new Railing(-1.75, 4.01, 5.4-17, 1, 12);
        if (i == 4)railing[i] = new Railing(-2.05, 4.01, 5.4 - 15.2, 0, 2);
        if (i == 5)railing[i] = new Railing(-3.85, 4.01, 5.4 - 15, 1, 2);
        railing[i]->initial();
    }

    console = new Console(-5.3, -12.7, -90);
    Console::initial();

    //LoadContainers();
    Object::init_line();
    Shelf::initial();
    Container::initial();
    Forklift::initial();
    Transporter::initial();

    //ImGui Preparations
    IMGUI_CHECKVERSION();                                                           //
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    while (!glfwWindowShouldClose(window))
    {
        if (control_panel)                                                          //
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        else
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        if (speedup) c_speed = 8.0;
        else c_speed = 5.0;
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);
        glfwSetKeyCallback(window, key_callback);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f); 

        line_shader.use();
        line_shader.setMat4("view", camera.GetViewMatrix());
        line_shader.setMat4("projection", projection);
        Object::select(selected_index);
        Object::DrawFrame(line_shader);

        
        area.use();
        area.setInt("material.diffuse", 0);
        area.setInt("material.specular", 0);
        area.setMat4("projection", projection);
        area.setMat4("view", view);
        area.setVec3("viewPos", camera.Position);
        area.setVec3("dirLight.direction", 0.0f, -1.0f, 0.0f);
        area.setVec3("dirLight.ambient", 0.01f, 0.01f, 0.01f);
        area.setVec3("dirLight.diffuse", 0.1f, 0.1f, 0.1f);
        area.setVec3("dirLight.specular", 0.2f, 0.2f, 0.2f);
        
        area.setFloat("material.shininess", 8.0f);
        for (int i = 0; i < 20; i++) {
            std::string head = "pointLights[" + std::to_string(i) + "]";
            std::string position = head + ".position";
            std::string ambient = head + ".ambient";
            std::string diffuse = head + ".diffuse";
            std::string specular = head + ".specular";
            std::string constant = head + ".constant";
            std::string linear = head + ".linear";
            std::string quadratic = head + ".quadratic";
            area.setVec3(position, pointLightPositions[i]);
            area.setVec3(ambient, 0.05f, 0.05f, 0.05f);
            area.setVec3(diffuse, 0.4f, 0.4f, 0.4f);
            area.setVec3(specular, 0.5f, 0.5f, 0.5f);
            area.setFloat(constant, 1.0f);
            area.setFloat(linear, 0.09f);
            area.setFloat(quadratic, 0.032f);
        }
        Ground->draw(area);
        area_back.use();
        area_back.setMat4("projection", projection);
        area_back.setMat4("view", view);
        Floor->draw(area_back);
        Wall->draw(area_back);
        Roof->draw(area_back);
        
        //lift
        lift.use();
        lift.setMat4("projection", projection);
        lift.setMat4("view", view);
        float locc = Lift->draw(10.5f, 0.0f, 12.2f, lift, upflag, protect1,
            uprotect1, locy, protect3, floor1,
            openflag, protect2, uprotect, in_it,
            loc1, protect, loc, openflag1,
            camera.Position);
        if ((upflag == 1 || upflag == 2) && Lift->inlift(camera.Position) && viewtype) camera.Position.y = locc + 1.3;


        norm_shader.use();
        norm_shader.setMat4("view", camera.GetViewMatrix());
        norm_shader.setMat4("projection", projection);
        norm_shader.setVec3("viewPos", camera.Position);
        norm_shader.setVec3("dirLight.direction", 0.0f, -1.0f, 0.0f);
        norm_shader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        norm_shader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        norm_shader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        norm_shader.setVec3("viewPos", camera.Position);
        norm_shader.setFloat("material.shininess", 32.0f);
        for (int i = 0; i < 20; i++) {
            std::string head = "pointLights[" + std::to_string(i) + "]";
            std::string position = head + ".position";
            std::string ambient = head + ".ambient";
            std::string diffuse = head + ".diffuse";
            std::string specular = head + ".specular";
            std::string constant = head + ".constant";
            std::string linear = head + ".linear";
            std::string quadratic = head + ".quadratic";
            norm_shader.setVec3(position, pointLightPositions[i]);
            norm_shader.setVec3(ambient, 0.05f, 0.05f, 0.05f);
            norm_shader.setVec3(diffuse, 0.8f, 0.8f, 0.8f);
            norm_shader.setVec3(specular, 1.0f, 1.0f, 1.0f);
            norm_shader.setFloat(constant, 1.0f);
            norm_shader.setFloat(linear, 0.09f);
            norm_shader.setFloat(quadratic, 0.032f);
        }
        




        if (operation == 1) {
            if (!objinobj(forklift, 0, 0))if (forklift->forward(1, deltaTime)) operation = 1;
        }
        else if (operation == 2) {
            if (!objinobj(forklift, 1, 0))if (forklift->backward(1, deltaTime)) operation = 2;
        }
        else if (operation == 3) {
            if (!objinobj(forklift, 2, 0))if (forklift->rotate(false)) operation = 0;
        }
        else if (operation == 4) {
            if (!objinobj(forklift, 3, 0))if (forklift->rotate(true)) operation = 0;
        }
        else if (operation == 5) {
            for (auto iter = Object::objects.begin(); iter != Object::objects.end(); iter++)
            {
                if (iter->second->GetType() != CONTAINER)continue;
                if (forklift->getbox(&(*iter->second)))
                    break;
            }
            operation = 0;
        }
        else if (operation == 6) {
            float temp_dis;
            float min_dis = 9999.0f;
            glm::vec3 temp_forklift_pos;
            glm::vec3 temp_shelf_pos;
            Object* target = NULL;
            for (auto iter = Object::objects.begin(); iter != Object::objects.end(); iter++)
            {
                if (iter->second->GetType() != object_type::SHELF && iter->second->GetType() != object_type::TRANSPORTER) continue;
                temp_forklift_pos = forklift->getPos();
                temp_shelf_pos = iter->second->getPos();
                temp_dis = fabsf(temp_forklift_pos.x - temp_shelf_pos.x) + fabsf(temp_forklift_pos.z - temp_shelf_pos.z);
                if (temp_dis < min_dis)
                {
                    target = iter->second;
                    min_dis = temp_dis;
                }
                
            }
            if (target != NULL)
                forklift->storebox(target);
            operation = 0;
        }
        else if (operation == 7) {
            if (forklift->rise(1, deltaTime))
                operation = 0;
        }
        else if (operation == 8) {
            if (forklift->decline(deltaTime))
                operation = 0;
        }

        for (auto iter = Object::objects.begin(); iter != Object::objects.end(); iter++) {
            if (iter->second->GetType() == object_type::TRANSPORTER) {
                ((Transporter*)iter->second)->rotate(deltaTime);
            }
            iter->second->draw(norm_shader);
        }
        
        glDepthFunc(GL_LEQUAL); 
        skyboxShader.use();
        skyboxShader.setMat4("view", glm::mat4(glm::mat3(camera.GetViewMatrix())));
        skyboxShader.setMat4("projection", projection);
        Skybox->draw();
        glDepthFunc(GL_LESS);

        //ImGui Frames
        ImGui_ImplOpenGL3_NewFrame();                                               //
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //ImGui Content
        DrawUI();

        //ImGui Render  
        ImGui::Render();                                                            //
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //ImGui shutdowns
    ImGui_ImplOpenGL3_Shutdown();                                                   //
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    if (key == GLFW_KEY_I && action == GLFW_PRESS)
        operation = 1;
    if (key == GLFW_KEY_K && action == GLFW_PRESS)
        operation = 2;
    if (key == GLFW_KEY_J && action == GLFW_PRESS)
        operation = 4;
    if (key == GLFW_KEY_L && action == GLFW_PRESS)
        operation = 3;
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
        operation = 5;
    if (key == GLFW_KEY_F && action == GLFW_PRESS)
        operation = 6;
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
        operation = 7;
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        operation = 8;

    if (key == GLFW_KEY_I && action == GLFW_RELEASE)
        operation = 0;
    if (key == GLFW_KEY_K && action == GLFW_RELEASE)
        operation = 0;
    if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
        operation = 0;
    if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
        operation = 0;
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        if (!viewtype || (viewtype && console->is_nearby(camera.Position))) {
            control_panel = !control_panel;
        }
    }            
}
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS && lock == 0) {
        lock = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE && lock) {
        viewtype = !viewtype;
        if (viewtype == 0) {
            firstview = camera.Position;
            camera.Position = overview;
        }
        else {
            overview = camera.Position;
            camera.Position = firstview;
        }
        lock = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        speedup = TRUE;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
        speedup = FALSE;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        //std::cout << viewtype << std::endl;
        int jx = 0, jz = 0;
        flush();
        initem(glm::vec3(camera.Position.x + camera.Front.x * camera.MovementSpeed * deltaTime, camera.Position.y, camera.Position.z + camera.Front.z * camera.MovementSpeed * deltaTime),camera.Position);
        judge_for_col(jx, jz);
        camera.ProcessKeyboard(FORWARD, deltaTime, camera.Position.y, openflag | openflag1, floor1, viewtype ? in_it : 0, jx, jz, viewtype,c_speed);
    }
        
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        int jx = 0, jz = 0;
        flush();
        initem(glm::vec3(camera.Position.x - camera.Front.x * camera.MovementSpeed * deltaTime, camera.Position.y, camera.Position.z - camera.Front.z * camera.MovementSpeed * deltaTime), camera.Position);
        judge_for_col(jx, jz);
        camera.ProcessKeyboard(BACKWARD, deltaTime, camera.Position.y, openflag | openflag1, floor1, viewtype ? in_it : 0, jx, jz, viewtype, c_speed);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        int jx = 0, jz = 0;
        flush();
        initem(glm::vec3(camera.Position.x + camera.Front.x * camera.MovementSpeed * deltaTime, camera.Position.y, camera.Position.z + camera.Front.z * camera.MovementSpeed * deltaTime), camera.Position);
        judge_for_col(jx, jz);
        camera.ProcessKeyboard(LEFT, deltaTime, camera.Position.y, openflag | openflag1, floor1, viewtype ? in_it : 0, jx, jz, viewtype, c_speed);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        int jx = 0, jz = 0;
        flush();
        initem(glm::vec3(camera.Position.x + camera.Front.x * camera.MovementSpeed * deltaTime, camera.Position.y, camera.Position.z + camera.Front.z * camera.MovementSpeed * deltaTime), camera.Position);
        judge_for_col(jx, jz);
        camera.ProcessKeyboard(RIGHT, deltaTime, camera.Position.y, openflag | openflag1, floor1, viewtype ? in_it : 0, jx, jz, viewtype,c_speed);
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS && viewtype) {
        if (nearlift()) {
            if (!protect && !protect1) {
                openflag += 1;
            }
            if (!uprotect && !uprotect1) {
                openflag1 += 1;
            }
        }
        
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS && viewtype) {
        if (!protect3 && ! protect2) {
            upflag += 1;
        }
    }
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;
    if (!control_panel) {
        camera.ProcessMouseMovement(xoffset, yoffset);
    }
        
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void inilight() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            pointLightPositions[i * 4 + j] = glm::vec3(-4.0 + 5.5*j, 6.09, 5.0 + 5.5*(i-3));
        }
    }
}

void initem(glm::vec3 pos, glm::vec3 pre_pos) {
    //int i = 0;
    for (auto iter = Container::territory.begin(); iter != Container::territory.end(); iter++) {
        if (iter->second == NULL) continue;
        col_dector_x.push_back(judge_one_x(pos, iter->second));
        col_dector_z.push_back(judge_one_z(pos, iter->second));
        col_dector_x_pre.push_back(judge_one_x(pre_pos, iter->second));
        col_dector_z_pre.push_back(judge_one_z(pre_pos, iter->second));
        //i++;
    }

}
int judge_one_x(glm::vec3 pos , float point[]) {
    if ((pos.x <= point[0] + 0.15 && pos.x >= point[1] - 0.15) || (pos.x <= point[1] + 0.15 && pos.x >= point[0] - 0.15))
        return 1;
    return 0;
}
int judge_one_z(glm::vec3 pos, float point[]) {
    if ((pos.z <= point[3] + 0.15 && pos.z >= point[2] - 0.15) || (pos.z <= point[2] + 0.15 && pos.z >= point[3] - 0.15))
        return 1;
    return 0;
}
void judge_for_col(int& x, int& z) {
    for (int i = 0; i < col_dector_x.size(); i++) {
        if (col_dector_x_pre[i] == 0 && col_dector_z_pre[i] == 0 && col_dector_x[i] == 1 && col_dector_z[i] == 1) {
            x = 1; z = 1; return;
        }
        if (col_dector_x_pre[i] == 1 && col_dector_z_pre[i] == 0 && col_dector_x[i] == 1 && col_dector_z[i] == 1) {
            z = 1;
        }
        if (col_dector_x_pre[i] == 0 && col_dector_z_pre[i] == 1 && col_dector_x[i] == 1 && col_dector_z[i] == 1) {
            x = 1;
        }
    }
    return;
}
void flush() {
    for (int i = 0; i < col_dector_x.size(); i++) {
        col_dector_x.pop_back();
        col_dector_x_pre.pop_back();
        col_dector_z.pop_back();
        col_dector_z_pre.pop_back();
    }
}

bool objinobj(Object* obj, int flag, int type) {
    bool res = false;
    int i = 0;
    float f[4] = { 0.0f };
    switch (flag) {
    case 0:
        if (type == 0) {
            Forklift* temp = (Forklift*)obj;
            temp->forward(1, deltaTime);
            for (auto iter = Shelf::territory.begin(); iter != Shelf::territory.end(); iter++) {
                if (iter->second == NULL) continue;
                if (i == 0) {
                    i++;
                    continue;
                }
                f[0] = iter->second[0]; f[1] = iter->second[1]; f[2] = iter->second[2]; f[3] = iter->second[3];
                if (!inside_room(Forklift::territory[0])) {
                    res = true;
                    break;
                }
                std::cout << " --------------------------------------" << std::endl;
                std::cout << f[0]<<" " << f[1] << " " << f[2] << " " << f[3] << std::endl;
                std::cout << Forklift::territory[0][0] << " " << Forklift::territory[0][1] << " " << Forklift::territory[0][2] << " " << Forklift::territory[0][3] << std::endl;
                std::cout << relationship(f, Forklift::territory[0]) << std::endl;
                std::cout << " --------------------------------------" << std::endl;
                if (relationship(f, Forklift::territory[0])) {
                    if (temp->box != NULL) {
                        if (temp->box->GetIndex() == iter->first) {
                            
                            continue;
                        }
                    }
                    res = true;
                    break;
                }
                
                
            }
            std::cout << "??" << std::endl;
            std::cout << "--------------" << std::endl;
            temp->backward(1, deltaTime);
        }
        break;
    case 1:
        if (type == 0) {
            Forklift* temp = (Forklift*)obj;
            temp->backward(1, deltaTime);
            for (auto iter = Shelf::territory.begin(); iter != Shelf::territory.end(); iter++) {
                if (iter->second == NULL) continue;
                if (i == 0) {
                    i++;
                    continue;
                }
                f[0] = iter->second[0]; f[1] = iter->second[1]; f[2] = iter->second[2]; f[3] = iter->second[3];
                if (!inside_room(Forklift::territory[0])) {
                    res = true;
                    break;
                }
                if (relationship(f, Forklift::territory[0])) {
                    if (temp->box != NULL) {
                        if (temp->box->GetIndex() == iter->first) {
                            continue;
                        }
                    }
                    res = true;
                    break;
                }
            }
            if (res) {
                while (1) {
                    i = 0;
                    temp->forward(1, deltaTime);
                    bool res1 = false;
                    for (auto iter = Shelf::territory.begin(); iter != Shelf::territory.end(); iter++) {
                        if (iter->second == NULL) continue;
                        if (i == 0) {
                            i++;
                            continue;
                        }
                        f[0] = iter->second[0]; f[1] = iter->second[1]; f[2] = iter->second[2]; f[3] = iter->second[3];
                        if (!inside_room(Forklift::territory[0])) {
                            res1 = true;
                            break;
                        }
                        if (relationship(f, Forklift::territory[0])) {
                            if (temp->box != NULL) {
                                if (temp->box->GetIndex() == iter->first) {
                                    continue;
                                }
                            }
                            res1 = true;
                            break;
                        }
                    }
                    if (!res1) break;
                }
            }
            else {
                temp->forward(1, deltaTime);
            }
        }
        break;
    case 2:
        if (type == 0) {
            Forklift* temp = (Forklift*)obj;
            temp->rotate(false);
            for (auto iter = Shelf::territory.begin(); iter != Shelf::territory.end(); iter++) {
                if (iter->second == NULL) continue;
                if (i == 0) {
                    i++;
                    continue;
                }
                f[0] = iter->second[0]; f[1] = iter->second[1]; f[2] = iter->second[2]; f[3] = iter->second[3];
                if (!inside_room(Forklift::territory[0])) {
                    res = true;
                    break;
                }
                if (relationship(f, Forklift::territory[0])) {
                    if (temp->box != NULL) {
                        if (temp->box->GetIndex() == iter->first) {
                            continue;
                        }
                    }
                    res = true;
                    break;
                }
            }
            temp->rotate(true);
        }
        break;
    case 3:
        if (type == 0) {
            Forklift* temp = (Forklift*)obj;
            temp->rotate(true);
            for (auto iter = Shelf::territory.begin(); iter != Shelf::territory.end(); iter++) {
                if (iter->second == NULL) continue;
                if (i == 0) {
                    i++;
                    continue;
                }
                f[0] = iter->second[0]; f[1] = iter->second[1]; f[2] = iter->second[2]; f[3] = iter->second[3];
                if (!inside_room(Forklift::territory[0])) {
                    res = true;
                    break;
                }
                if (relationship(f, Forklift::territory[0])) {
                    if (temp->box != NULL) {
                        if (temp->box->GetIndex() == iter->first) {
                            continue;
                        }
                    }
                    res = true;
                    break;
                }
            }
            temp->rotate(false);
        }
        break;
    default:
        break;
    }
    return res;

}
bool relationship(float f1[], float f2[]) {
    if (f1[0] <= max(f2[0], f2[1]) && f1[0] >= min(f2[0], f2[1]) && f1[2] <= max(f2[2], f2[3]) && f1[2] >= min(f2[2], f2[3]))return true;
    if (f1[0] <= max(f2[0], f2[1]) && f1[0] >= min(f2[0], f2[1]) && f1[3] <= max(f2[2], f2[3]) && f1[3] >= min(f2[2], f2[3]))return true;
    if (f1[1] <= max(f2[0], f2[1]) && f1[1] >= min(f2[0], f2[1]) && f1[2] <= max(f2[2], f2[3]) && f1[2] >= min(f2[2], f2[3]))return true;
    if (f1[1] <= max(f2[0], f2[1]) && f1[1] >= min(f2[0], f2[1]) && f1[3] <= max(f2[2], f2[3]) && f1[3] >= min(f2[2], f2[3]))return true;
    if (f2[0] <= max(f1[0], f1[1]) && f2[0] >= min(f1[0], f1[1]) && f2[2] <= max(f1[2], f1[3]) && f2[2] >= min(f1[2], f1[3]))return true;
    if (f2[0] <= max(f1[0], f1[1]) && f2[0] >= min(f1[0], f1[1]) && f2[3] <= max(f1[2], f1[3]) && f2[3] >= min(f1[2], f1[3]))return true;
    if (f2[1] <= max(f1[0], f1[1]) && f2[1] >= min(f1[0], f1[1]) && f2[2] <= max(f1[2], f1[3]) && f2[2] >= min(f1[2], f1[3]))return true;
    if (f2[1] <= max(f1[0], f1[1]) && f2[1] >= min(f1[0], f1[1]) && f2[3] <= max(f1[2], f1[3]) && f2[3] >= min(f1[2], f1[3]))return true;
    
    return false;
}

bool inside_room(float pos[]) {
    if (max(pos[0], pos[1]) <= 11.7 && max(pos[2], pos[3]) <= 12.2 && min(pos[0], pos[1]) >= -5.7 && min(pos[2], pos[3]) >= -13.2) return true;
    return false;
}
bool nearlift() {
    if (camera.Position.x <= 11.7 && camera.Position.x >= 7.7 && camera.Position.z >= 9.7) return true;
    return false;
}

void DrawUI()
{
    if (control_panel)
    {
        ImGui::Begin("Control Panel", &control_panel);
        //Welcome part:
        {
            ImGui::Text("+------------------------------------+");
            ImGui::Text("| Welcome! Here is the control panel.|");
            ImGui::Text("| Basic operations are below:        |");
            ImGui::Text("+------------------------------------+");
            ImGui::Text("| WASD: move around                  |");
            ImGui::Text("| IJKL: forklift movement            |");
            ImGui::Text("| E:    get the container            |");
            ImGui::Text("| F:    store the container          |");
            ImGui::Text("| R:    close/reopen the menu        |");
            ImGui::Text("+------------------------------------+");
        }
        //Selection part:
        {
            ImGui::BulletText("Select Part:");
            ImGui::Text("  "); ImGui::SameLine();
            if (ImGui::Button(" Forklift ")) {
                forklift_selected = true;
                container_selected = false;
                shelf_selected = false;
                transporter_selected = false;
                //std::cout << "-----------------------------------------" << std::endl;
                for (auto iter = Object::objects.begin(); iter != Object::objects.end(); iter++)
                {
                    if (iter->second->GetType() != object_type::FORKLIFT) continue;
                    selected_index = iter->first;
                    break;
                }
            }
            ImGui::SameLine();
            if (ImGui::Button(" last1 ")) {
                int previous_index = selected_index;
                for (auto iter = Object::objects.begin(); iter != Object::objects.end(); iter++)
                {
                    if (iter->second->GetType() != object_type::FORKLIFT) continue;
                    if (iter->first >= previous_index) continue;
                    selected_index = iter->first;
                }
            }
            ImGui::SameLine();
            if (ImGui::Button(" next1 ")) {
                for (auto iter = Object::objects.begin(); iter != Object::objects.end(); iter++)
                {
                    if (iter->second->GetType() != object_type::FORKLIFT) continue;
                    if (iter->first <= selected_index) continue;
                    selected_index = iter->first;
                    break;
                }
            }
            ImGui::Text("  "); ImGui::SameLine();
            if (ImGui::Button("Container ")) {
                forklift_selected = false;
                container_selected = true;
                shelf_selected = false;
                transporter_selected = false;
                //std::cout << "-----------------------------------------" << std::endl;
                for (auto iter = Object::objects.begin(); iter != Object::objects.end(); iter++)
                {
                    if (iter->second->GetType() != object_type::CONTAINER) continue;
                    selected_index = iter->first;
                    break;
                }
                std::cout << "Selected container: " << selected_index << std::endl;
            }
            ImGui::SameLine();
            if (ImGui::Button(" last2 ")) {
                int previous_index = selected_index;
                for (auto iter = Object::objects.begin(); iter != Object::objects.end(); iter++)
                {
                    if (iter->second->GetType() != object_type::CONTAINER) continue;
                    if (iter->first >= previous_index) continue;
                    selected_index = iter->first;
                }
            }
            ImGui::SameLine();
            if (ImGui::Button(" next2 ")) {
                for (auto iter = Object::objects.begin(); iter != Object::objects.end(); iter++)
                {
                    if (iter->second->GetType() != object_type::CONTAINER) continue;
                    if (iter->first <= selected_index) continue;
                    selected_index = iter->first;
                    break;
                }
            }
            ImGui::Text("  "); ImGui::SameLine();
            if (ImGui::Button("  Shelf   ")) {
                forklift_selected = false;
                container_selected = false;
                shelf_selected = true;
                transporter_selected = false;
                //std::cout << "-----------------------------------------" << std::endl;
                for (auto iter = Object::objects.begin(); iter != Object::objects.end(); iter++)
                {
                    if (iter->second->GetType() != object_type::SHELF) continue;
                    selected_index = iter->first;
                    break;
                }
            }
            ImGui::SameLine();
            if (ImGui::Button(" last3 ")) {
                int previous_index = selected_index;
                for (auto iter = Object::objects.begin(); iter != Object::objects.end(); iter++)
                {
                    if (iter->second->GetType() != object_type::SHELF) continue;
                    if (iter->first >= previous_index) continue;
                    selected_index = iter->first;
                }
            }
            ImGui::SameLine();
            if (ImGui::Button(" next3 ")) {
                for (auto iter = Object::objects.begin(); iter != Object::objects.end(); iter++)
                {
                    if (iter->second->GetType() != object_type::SHELF) continue;
                    if (iter->first <= selected_index) continue;
                    selected_index = iter->first;
                    break;
                }
            }
            ImGui::Text("  "); ImGui::SameLine();
            if (ImGui::Button(" Conveyor ")) {
                forklift_selected = false;
                container_selected = false;
                shelf_selected = false;
                transporter_selected = true;
                //std::cout << "-----------------------------------------" << std::endl;
                for (auto iter = Object::objects.begin(); iter != Object::objects.end(); iter++)
                {
                    if (iter->second->GetType() != object_type::TRANSPORTER) continue;
                    selected_index = iter->first;
                    break;
                }
            }
            ImGui::SameLine();
            if (ImGui::Button(" last4 ")) {
                int previous_index = selected_index;
                for (auto iter = Object::objects.begin(); iter != Object::objects.end(); iter++)
                {
                    if (iter->second->GetType() != object_type::TRANSPORTER) continue;
                    if (iter->first >= previous_index) continue;
                    selected_index = iter->first;
                }
            }
            ImGui::SameLine();
            if (ImGui::Button(" next4 ")) {
                for (auto iter = Object::objects.begin(); iter != Object::objects.end(); iter++)
                {
                    if (iter->second->GetType() != object_type::TRANSPORTER) continue;
                    if (iter->first <= selected_index) continue;
                    selected_index = iter->first;
                    break;
                }
            }
            if (selected_index == -1)
                ImGui::Text("   Current selected index is null. ");
            else
                ImGui::Text("   Current selected index is %d.   ", selected_index);
            if (container_selected)
                ImGui::Text("   This is a container.");
            else if (forklift_selected)
                ImGui::Text("   This is a forklift.");
            else if (shelf_selected)
                ImGui::Text("   This is a shelf.");
            else if (transporter_selected)
                ImGui::Text("   This is a conveyor.");
            else
                ImGui::Text("   Nothing is selected.");
        }
        //Edit part:
        {
            ImGui::BulletText("Edit Part:");
            ImGui::Text("  "); ImGui::SameLine();
            ImGui::Checkbox("EditMode", &edit_mode);
            ImGui::SameLine();
            if (ImGui::Button("Reset"))
            {
                forklift_selected = false;
                container_selected = false;
                shelf_selected = false;
                transporter_selected = false;
                selected_index = -1;
            }
            ImGui::Text("       "); ImGui::SameLine();
            if (ImGui::Button(" A "))
            {
                if (edit_mode && selected_index != -1)
                {
                    glm::vec3 current_pos = Object::objects[selected_index]->getPos();
                    Object::objects[selected_index]->SetPos(current_pos.x + 1.0, current_pos.y, current_pos.z);
                }
            }
            ImGui::Text("  "); ImGui::SameLine();
            if (ImGui::Button(" < "))
            {
                if (edit_mode && selected_index != -1)
                {
                    glm::vec3 current_pos = Object::objects[selected_index]->getPos();
                    Object::objects[selected_index]->SetPos(current_pos.x, current_pos.y, current_pos.z - 1.0);
                }
            }
            ImGui::SameLine();
            if (ImGui::Button(" V ")) {
                if (edit_mode && selected_index != -1)
                {
                    glm::vec3 current_pos = Object::objects[selected_index]->getPos();
                    Object::objects[selected_index]->SetPos(current_pos.x - 1.0, current_pos.y, current_pos.z);
                }
            }
            ImGui::SameLine();
            if (ImGui::Button(" > ")) {
                if (edit_mode && selected_index != -1)
                {
                    glm::vec3 current_pos = Object::objects[selected_index]->getPos();
                    Object::objects[selected_index]->SetPos(current_pos.x, current_pos.y, current_pos.z + 1.0);
                }
            }
            ImGui::SameLine();
            ImGui::Text(" ");
            ImGui::SameLine();
            if (ImGui::Button(" ROTATE ")) {
                if (edit_mode && selected_index != -1)
                {
                    if (Object::objects[selected_index]->GetType() == SHELF)
                    {
                        Shelf* temp_shelf = (Shelf*)Object::objects[selected_index];
                        temp_shelf->rotate();
                    }
                    if (Object::objects[selected_index]->GetType() == TRANSPORTER)
                    {
                        Transporter* temp_transporter = (Transporter*)Object::objects[selected_index];
                        temp_transporter->rotate();
                    }
                }
            }
            ImGui::Text("  "); ImGui::SameLine();
            if (ImGui::Button("ADD CONTAINER"))
            {
                if (edit_mode)
                {
                    container_num++;
                    container = new Container(0.0, 9.5 + container_num * container_distance, 0);
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("DEL CONTAINER"))
            {
                if (edit_mode && container_num > 0)
                {
                    container_num--;
                    int target_index = -1;
                    for (auto iter = Object::objects.begin(); iter != Object::objects.end(); iter++)
                    {
                        if (iter->second->GetType() != CONTAINER)continue;
                        target_index = iter->first;
                    }
                    //std::cout << "Delete target index is: " << target_index << std::endl;
                    for (auto iter = Object::objects.begin(); iter != Object::objects.end(); )
                    {
                        if (iter->first == target_index)
                            iter = Object::objects.erase(iter);
                        else
                            iter++;
                    }
                    for (auto iter = Object::territory.begin(); iter != Object::territory.end(); )
                    {
                        if (iter->first == target_index)
                            iter = Object::territory.erase(iter);
                        else
                            iter++;
                    }
                }
            }
            ImGui::Text("  "); ImGui::SameLine();
            if (ImGui::Button("ADD SHELF    "))
            {
                if (edit_mode)
                {
                    shelf_num++;
                    shelf = new Shelf(x_corner + shelf_num * 3.0, z_corner, true, default_shelf_length);
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("DEL SHELF    "))
            {
                if (edit_mode && shelf_num > 0)
                {
                    shelf_num--;
                    int target_index = -1;
                    for (auto iter = Object::objects.begin(); iter != Object::objects.end(); iter++)
                    {
                        if (iter->second->GetType() != SHELF)continue;
                        target_index = iter->first;
                    }
                    //std::cout << "Delete target index is: " << target_index << std::endl;
                    for (auto iter = Object::objects.begin(); iter != Object::objects.end(); )
                    {
                        if (iter->first == target_index)
                            iter = Object::objects.erase(iter);
                        else
                            iter++;
                    }
                    for (auto iter = Object::territory.begin(); iter != Object::territory.end(); )
                    {
                        if (iter->first == target_index)
                            iter = Object::territory.erase(iter);
                        else
                            iter++;
                    }
                }
            }
            ImGui::SameLine();
            ImGui::SetNextItemWidth(70);
            ImGui::InputInt("Default Shelf Length", &default_shelf_length);
            ImGui::Text("  "); ImGui::SameLine();
            if (ImGui::Button("ADD CONVEYOR "))
            {
                if (edit_mode)
                {
                    transporter_num++;
                    transporter = new Transporter(x_corner - 3, z_corner - 5.0 - transporter_num * 2.0, true, default_transporter_length);
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("DEL CONVEYOR "))
            {
                if (edit_mode && transporter_num > 0)
                {
                    transporter_num--;
                    int target_index = -1;
                    for (auto iter = Object::objects.begin(); iter != Object::objects.end(); iter++)
                    {
                        if (iter->second->GetType() != TRANSPORTER)continue;
                        target_index = iter->first;
                    }
                    //std::cout << "Delete target index is: " << target_index << std::endl;
                    for (auto iter = Object::objects.begin(); iter != Object::objects.end(); )
                    {
                        if (iter->first == target_index)
                            iter = Object::objects.erase(iter);
                        else
                            iter++;
                    }
                    for (auto iter = Object::territory.begin(); iter != Object::territory.end(); )
                    {
                        if (iter->first == target_index)
                            iter = Object::territory.erase(iter);
                        else
                            iter++;
                    }
                }
            }
            ImGui::SameLine();
            ImGui::SetNextItemWidth(70);
            ImGui::InputInt("Default Conveyor Length", &default_transporter_length);
        }
        //Archive part:
        {
            ImGui::BulletText("Archive Part:");
            ImGui::Text("  "); ImGui::SameLine();
            if (ImGui::Button("Save Containers"))
            {
                SaveContainers();
            }
            ImGui::SameLine();
            if (ImGui::Button("Load Containers"))
            {
                LoadContainers();
            }
            ImGui::SameLine();
            time_t time1 = get_mtime(".\\saves\\container.txt");
            struct tm* t1 = new struct tm;
            localtime_s(t1, &time1);
            ImGui::Text("Last record: %02d:%02d:%02d", t1->tm_hour, t1->tm_min, t1->tm_sec);

            ImGui::Text("  "); ImGui::SameLine();
            if (ImGui::Button("Save Shelves   "))
            {
                SaveShelves();
            }
            ImGui::SameLine();
            if (ImGui::Button("Load Shelves   "))
            {
                LoadShelves();
            }
            ImGui::SameLine();
            time_t time2 = get_mtime(".\\saves\\shelf.txt");
            struct tm* t2 = new struct tm;
            localtime_s(t2, &time2);
            ImGui::Text("Last record: %02d:%02d:%02d", t2->tm_hour, t2->tm_min, t2->tm_sec);

            ImGui::Text("  "); ImGui::SameLine();
            if (ImGui::Button("Save Conveyors "))
            {
                SaveTransporters();
            }
            ImGui::SameLine();
            if (ImGui::Button("Load Conveyors "))
            {
                LoadTransporters();
            }
            ImGui::SameLine();
            time_t time3 = get_mtime(".\\saves\\transporter.txt");
            struct tm* t3 = new struct tm;
            localtime_s(t3, &time3);
            ImGui::Text("Last record: %02d:%02d:%02d", t3->tm_hour, t3->tm_min, t3->tm_sec);
        }
        //Exit part:
        {
            ImGui::BulletText("Exit Part:");
            time_t now_time = time(NULL);
            struct tm* tnow = new struct tm;
            localtime_s(tnow, &now_time);
            ImGui::Text("  "); ImGui::SameLine();
            ImGui::Text("Current time: %02d:%02d:%02d", tnow->tm_hour, tnow->tm_min, tnow->tm_sec);
            ImGui::Text("  "); ImGui::SameLine();
            if (ImGui::Button("Close Panel"))
                control_panel = false;
            ImGui::End();
        }
    }
}


time_t get_mtime(std::string filename)
{
    struct stat result;
    if (stat(filename.c_str(), &result) == 0)
    {
        auto mod_time = result.st_mtime;
        return mod_time;
    }
    return -1;
}

void SaveContainers()													//
{
    std::cout << "containers saving... ..." << std::endl;
    std::fstream outfile;
    outfile.open(".\\saves\\container.txt", std::ios::out);
    outfile << container_num << std::endl;
    for (auto iter = Container::objects.begin(); iter != Container::objects.end(); iter++) {
        if (iter->second->GetType() != object_type::CONTAINER) continue;
        outfile << iter->second->getPos().x << " " << iter->second->getPos().y << " " << iter->second->getPos().z << std::endl;
    }
    outfile.close();
    std::cout << "container positions are saved in '/saves/container.txt'!" << std::endl;
}
void LoadShelves()                                                              //
{
    std::cout << "shelves loading... ..." << std::endl;
    std::fstream infile;
    infile.open("./saves/shelf.txt", std::ios::in);
    infile >> shelf_num;
    for (int i = 0; i < shelf_num; i++)
    {
        float tempx, tempy, tempz;
        bool temp_front;
        int temp_length;
        glm::vec3 temp_pos;
        infile >> tempx >> tempy >> tempz >> temp_front >> temp_length;
        temp_pos = glm::vec3(tempx, tempy, tempz);
        shelf_pos.push_back(temp_pos);
        shelf = new Shelf(tempx, tempz, temp_front, temp_length);
    }
    std::cout << "shelves are loaded!" << std::endl;
}
void LoadContainers()															//
{
    std::cout << "containers loading... ..." << std::endl;
    std::fstream infile;
    infile.open("./saves/container.txt", std::ios::in);
    infile >> container_num;
    for (int i = 0; i < container_num; i++)
    {
        float tempx, tempy, tempz;
        glm::vec3 temp_pos;
        infile >> tempx >> tempy >> tempz;
        std::cout << tempx << " " << tempy << " " << tempz << std::endl;
        temp_pos = glm::vec3(tempx, tempy, tempz);
        container_pos.push_back(temp_pos);
        container = new Container(tempx, tempz, 0);
    }
    std::cout << "containers are loaded!" << std::endl;
}
void SaveShelves()                                                      //
{
    std::cout << "shelves saving... ..." << std::endl;
    std::fstream outfile;
    Shelf* temp_shelf = NULL;
    outfile.open(".\\saves\\shelf.txt", std::ios::out);
    outfile << shelf_num << std::endl;
    for (auto iter = Object::objects.begin(); iter != Object::objects.end(); iter++) {
        if (iter->second->GetType() != object_type::SHELF) continue;
        temp_shelf = (Shelf*)iter->second;
        outfile << temp_shelf->getPos().x << " " << temp_shelf->getPos().y << " " << temp_shelf->getPos().z << " " << temp_shelf->get_front() << " " << temp_shelf->get_length() << std::endl;
    }
    outfile.close();
    std::cout << "shelves statuses are saved in '/saves/shelf.txt'!" << std::endl;
}

void LoadTransporters()                                                              //
{
    std::cout << "transporters loading... ..." << std::endl;
    std::fstream infile;
    infile.open("./saves/transporter.txt", std::ios::in);
    infile >> transporter_num;
    for (int i = 0; i < transporter_num; i++)
    {
        float tempx, tempy, tempz;
        int temp_length;
        bool temp_front;
        glm::vec3 temp_pos;
        infile >> tempx >> tempy >> tempz >> temp_front >> temp_length;
        temp_pos = glm::vec3(tempx, tempy, tempz);
        transporter_pos.push_back(temp_pos);
        transporter = new Transporter(tempx, tempz, temp_front, temp_length);
    }
    std::cout << "transporters are loaded!" << std::endl;
}

void SaveTransporters()                                                      //
{
    std::cout << "transporter saving... ..." << std::endl;
    std::fstream outfile;
    Transporter* temp_transpoter = NULL;
    outfile.open(".\\saves\\transporter.txt", std::ios::out);
    outfile << transporter_num << std::endl;
    for (auto iter = Object::objects.begin(); iter != Object::objects.end(); iter++) {
        if (iter->second->GetType() != object_type::TRANSPORTER) continue;
        temp_transpoter = (Transporter*)iter->second;
        outfile << temp_transpoter->getPos().x << " " << temp_transpoter->getPos().y << " " << temp_transpoter->getPos().z << " " << temp_transpoter->get_front() << " " << temp_transpoter->GetLen() << std::endl;
    }
    outfile.close();
    std::cout << "transporter statuses are saved in 'ves/transporter.txt'!" << std::endl;
}