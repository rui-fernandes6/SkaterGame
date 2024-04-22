#include "DirectX.h"
#include <Keyboard.h>

const int Width = 800;
const int Height = 708;
const float framerate = 30;
bool gameover;
int game_state = 0, game2_state = 0;
int game_flag = 0, menuflag = 1, menulevelsflag = 0, game2_flag = 0;
int score = 0, score2 =0, score3=0, highscore1 = 0, highscore2 = 0;
int road_pos = 300, world_width = 4668, world_height = 708;
float skater_speed = 18, skaterFlappy_speed=5;
float duck_speed = 20, BottomSkater;
POINT p;
static int jump = 0;
int goingdown = 0;

Keyboard::KeyboardStateTracker keyboardtracker;
Mouse::ButtonStateTracker mousetracker;
Model2D background, mainmenu, menulevels, skater, startButton, obstacle1, obstacle1_1, obstacle2, obstacle2_2, obstacle3, obstacle3_3, obstacle4, obstacle4_4, obstacle5, obstacle5_5, ball, spikes, duckbehind1, duck1, duckbehind2, duck2, backgroundGame2, obstacle1Flappy, obstacle2Flappy, skaterFlappy, obstacle1FlappyFront, obstacle2FlappyFront, ball2, spikes2, ball3, spikes3, ball4, spikes4, ball5, spikes5, ball6, spikes6, ball7, spikes7, obstacle3Flappy, obstacle3FlappyFront, obstacle4Flappy,obstacle4FlappyFront, obstacle5Flappy, obstacle5FlappyFront, obstacle6Flappy, obstacle6FlappyFront, obstacle7Flappy, obstacle7FlappyFront, obstacle8Flappy, obstacle8FlappyFront, obstacle9Flappy, obstacle9FlappyFront, obstacle10Flappy, obstacle10FlappyFront, obstacle11Flappy, obstacle11FlappyFront, obstacle12Flappy, obstacle12FlappyFront, obstacle13Flappy, obstacle13FlappyFront, obstacle14Flappy, obstacle14FlappyFront, obstacle15Flappy, obstacle15FlappyFront, obstacle16Flappy, obstacle16FlappyFront, obstacle17Flappy, obstacle17FlappyFront, obstacle18Flappy, obstacle18FlappyFront, obstacle19Flappy, obstacle19FlappyFront, obstacle20Flappy, obstacle20FlappyFront, obstacle21Flappy, obstacle21FlappyFront, obstacle22Flappy, obstacle22FlappyFront, obstacle23Flappy, obstacle23FlappyFront, obstacle24Flappy, obstacle24FlappyFront, obstacle25Flappy, obstacle25FlappyFront, obstacle26Flappy, obstacle26FlappyFront, obstacle27Flappy, obstacle27FlappyFront, obstacle28Flappy, obstacle28FlappyFront;

std::unique_ptr<SoundEffect> soundEffect;
std::unique_ptr<SoundEffectInstance> effectInstance;
std::unique_ptr<SoundEffect> duck;
std::unique_ptr<SoundEffect> jumpingFlappy;
std::unique_ptr<SoundEffect> crash;
std::unique_ptr<SpriteFont> spriteFont;

void UpdateSkater();
void UpdateDuckBehind1();
void UpdateDuck1();
void UpdateDuckBehind2();
void UpdateDuck2();
void UpdateSkaterFlappy();
void UpdateScore();

bool Game_Init(HWND hwnd)
{
    gameover = false;

    if (InitD3D(hwnd) == false)
        return false;
    if (InitInput(hwnd) == false)
        return false;
    if (InitSound() == false)
        return false;
    
    if (GetCursorPos(&p))
    {
        //cursor position now in p.x and p.y
    }

    skater = CreateModel2D(L"skaterskating2-removebg-preview2.png", 4, 4);
    if (skater.texture == NULL)
    {
        MessageBox(NULL, L"Loading skaterskating.png error",
            L"Error", MB_OK | MB_ICONERROR);
    }
    skater.x = Width / 2;
    skater.y = road_pos;
    skater.frame = 1;

    mainmenu = CreateModel2D(L"MainMenu2_2.png");
    if (mainmenu.texture == NULL)
        return false;
    mainmenu.x = 0;
    mainmenu.y = 0;

    menulevels = CreateModel2D(L"MenuLevels_2_2.png");
    if (menulevels.texture == NULL)
        return false;
    menulevels.x = 0;
    menulevels.y = 0;

    //GAME1 DEFINITIONS
    background = CreateModel2D(L"Myroad2.png");
    if (background.texture == NULL)
        return false;
    
    obstacle1 = CreateModel2D(L"obstacle1.png");
    if (obstacle1.texture == NULL)
        return false;
    obstacle1.x = 900; obstacle1.y = 400;
    obstacle1_1 = CreateModel2D(L"obstacle1_1.png");
    if (obstacle1_1.texture == NULL)
        return false;
    obstacle1_1.x = 820; obstacle1_1.y = 390;
    //
    obstacle2 = CreateModel2D(L"obstacle2.png");
    if (obstacle2.texture == NULL)
        return false;
    obstacle2.x = 1500; obstacle2.y = 400;
    obstacle2_2 = CreateModel2D(L"obstacle2_2.png");
    if (obstacle2_2.texture == NULL)
        return false;
    obstacle2_2.x = 1440; obstacle2_2.y = 390;
    //
    obstacle3 = CreateModel2D(L"obstacle3.png");
    if (obstacle3.texture == NULL)
        return false;
    obstacle3.x = 1750; obstacle3.y = 400;
    obstacle3_3 = CreateModel2D(L"obstacle3_3.png");
    if (obstacle3_3.texture == NULL)
        return false;
    obstacle3_3.x = 1690; obstacle3_3.y = 390;
    //
    obstacle4 = CreateModel2D(L"obstacle3.png");
    if (obstacle4.texture == NULL)
        return false;
    obstacle4.x = 2500; obstacle4.y = 400;
    obstacle4_4 = CreateModel2D(L"obstacle3_3.png");
    if (obstacle4_4.texture == NULL)
        return false;
    obstacle4_4.x = 2440; obstacle4_4.y = 390;
    //
    obstacle5 = CreateModel2D(L"obstacle3.png");
    if (obstacle5.texture == NULL)
        return false;
    obstacle5.x = 3300; obstacle5.y = 400;
    obstacle5_5 = CreateModel2D(L"obstacle5_5.png");
    if (obstacle5_5.texture == NULL)
        return false;
    obstacle5_5.x = 3240; obstacle5_5.y = 390;
    //
    ball = CreateModel2D(L"ball.png");
    if (ball.texture == NULL)
        return false;
    ball.x = 300; ball.y = 450;
    //
    spikes = CreateModel2D(L"spikes.png");
    if (spikes.texture == NULL)
        return false;
    spikes.x = 230; spikes.y = 420;
    //
    ball2 = CreateModel2D(L"ball.png");
    if (ball2.texture == NULL)
        return false;
    ball2.x = 2300; ball2.y = 450;
    //
    spikes2 = CreateModel2D(L"spikes.png");
    if (spikes2.texture == NULL)
        return false;
    spikes2.x = 2230; spikes2.y = 420;
    //
    ball3 = CreateModel2D(L"ball.png");
    if (ball3.texture == NULL)
        return false;
    ball3.x = 2670; ball3.y = 450;
    //
    spikes3 = CreateModel2D(L"spikes.png");
    if (spikes3.texture == NULL)
        return false;
    spikes3.x = 2600; spikes3.y = 420;
    //
    ball4 = CreateModel2D(L"ball.png");
    if (ball4.texture == NULL)
        return false;
    ball4.x = 3000; ball4.y = 450;
    //
    spikes4 = CreateModel2D(L"spikes.png");
    if (spikes4.texture == NULL)
        return false;
    spikes4.x = 2930; spikes4.y = 420;
    //
    ball4 = CreateModel2D(L"ball.png");
    if (ball4.texture == NULL)
        return false;
    ball4.x = 3000; ball4.y = 450;
    //
    spikes4 = CreateModel2D(L"spikes.png");
    if (spikes4.texture == NULL)
        return false;
    spikes4.x = 2930; spikes4.y = 420;
    //
    ball5 = CreateModel2D(L"ball.png");
    if (ball5.texture == NULL)
        return false;
    ball5.x = 3480; ball5.y = 450;
    //
    spikes5 = CreateModel2D(L"spikes.png");
    if (spikes5.texture == NULL)
        return false;
    spikes5.x = 3410; spikes5.y = 420;
    //
    ball6 = CreateModel2D(L"ball.png");
    if (ball6.texture == NULL)
        return false;
    ball6.x = 3800; ball6.y = 450;
    //
    spikes6 = CreateModel2D(L"spikes.png");
    if (spikes6.texture == NULL)
        return false;
    spikes6.x = 3730; spikes6.y = 420;
    //
    ball7 = CreateModel2D(L"ball.png");
    if (ball7.texture == NULL)
        return false;
    ball7.x = 4200; ball7.y = 450;
    //
    spikes7 = CreateModel2D(L"spikes.png");
    if (spikes7.texture == NULL)
        return false;
    spikes7.x = 4130; spikes7.y = 420;
    //
    duckbehind1 = CreateModel2D(L"ball.png", 6, 4);
    if (duckbehind1.texture == NULL)
        return false;
    duckbehind1.x = 4600; duckbehind1.y = 200; 
    duckbehind1.move_x = -duck_speed;
    //
    duckbehind2 = CreateModel2D(L"ball.png", 6, 4);
    if (duckbehind2.texture == NULL)
        return false;
    duckbehind2.x = 1800; duckbehind2.y = 200;
    duckbehind2.move_x = -duck_speed;
    //
    duck1 = CreateModel2D(L"duck.png", 6, 4);
    if (duck1.texture == NULL)
        return false;
    duck1.x = 4550; duck1.y = 180;
    duck1.move_x = -duck_speed;
    //
    duck2 = CreateModel2D(L"duck.png", 6, 4);
    if (duck2.texture == NULL)
        return false;
    duck2.x = 1750; duck2.y = 180;
    duck2.move_x = -duck_speed;

    //GAME2 DEFINITIONS

    backgroundGame2 = CreateModel2D(L"Myroad2_2.png");
    if (backgroundGame2.texture == NULL)
        return false;

    skaterFlappy = CreateModel2D(L"skaterskating2-removebg-preview2.png", 4, 4);
    if (skaterFlappy.texture == NULL)
        return false;
    skaterFlappy.x = 50; skaterFlappy.y = road_pos;
    skaterFlappy.move_x = skaterFlappy_speed;
    skaterFlappy.frame = 1;

    obstacle1Flappy = CreateModel2D(L"Obstacle1_flappy_Behind.bmp");
    if (obstacle1Flappy.texture == NULL)
        return false;
    obstacle1Flappy.x = 515; obstacle1Flappy.y = 0;

    obstacle1FlappyFront = CreateModel2D(L"Obstacle1_flappy.bmp");
    if (obstacle1FlappyFront.texture == NULL)
        return false;
    obstacle1FlappyFront.x = 460; obstacle1FlappyFront.y = 0;
    
    obstacle2Flappy = CreateModel2D(L"obstacleBehindTemplateFlappy.bmp");
    if (obstacle2Flappy.texture == NULL)
        return false;
    obstacle2Flappy.x = 510; obstacle2Flappy.y = 480;

    obstacle2FlappyFront = CreateModel2D(L"obstacleTemplateFlappy.bmp");
    if (obstacle2FlappyFront.texture == NULL)
        return false;
    obstacle2FlappyFront.x = 460; obstacle2FlappyFront.y = 450;

///////////2ND LINE////////////
    obstacle3Flappy = CreateModel2D(L"obstacleBehindTemplateFlappy.bmp");
    if (obstacle3Flappy.texture == NULL)
        return false;
    obstacle3Flappy.x = 810; obstacle3Flappy.y = -425;

    obstacle3FlappyFront = CreateModel2D(L"obstacleTemplateFlappy.bmp");
    if (obstacle3FlappyFront.texture == NULL)
        return false;
    obstacle3FlappyFront.x = 760; obstacle3FlappyFront.y = -385;

    obstacle4Flappy = CreateModel2D(L"obstacleBehindTemplateFlappy.bmp");
    if (obstacle4Flappy.texture == NULL)
        return false;
    obstacle4Flappy.x = 810; obstacle4Flappy.y = 568;

    obstacle4FlappyFront = CreateModel2D(L"obstacleTemplateFlappy.bmp");
    if (obstacle4FlappyFront.texture == NULL)
        return false;
    obstacle4FlappyFront.x = 760; obstacle4FlappyFront.y = 548;

    ///////////3RD LINE////////////
    obstacle5Flappy = CreateModel2D(L"obstacleBehindTemplateFlappy.bmp");
    if (obstacle5Flappy.texture == NULL)
        return false;
    obstacle5Flappy.x = 1110; obstacle5Flappy.y = -625;

    obstacle5FlappyFront = CreateModel2D(L"obstacleTemplateFlappy.bmp");
    if (obstacle5FlappyFront.texture == NULL)
        return false;
    obstacle5FlappyFront.x = 1060; obstacle5FlappyFront.y = -585;

    obstacle6Flappy = CreateModel2D(L"obstacleBehindTemplateFlappy.bmp");
    if (obstacle6Flappy.texture == NULL)
        return false;
    obstacle6Flappy.x = 1110; obstacle6Flappy.y = 373;

    obstacle6FlappyFront = CreateModel2D(L"obstacleTemplateFlappy.bmp");
    if (obstacle6FlappyFront.texture == NULL)
        return false;
    obstacle6FlappyFront.x = 1060; obstacle6FlappyFront.y = 353;

    ///////////4TH LINE////////////
    obstacle7Flappy = CreateModel2D(L"obstacleBehindTemplateFlappy.bmp");
    if (obstacle7Flappy.texture == NULL)
        return false;
    obstacle7Flappy.x = 1410; obstacle7Flappy.y = -550;

    obstacle7FlappyFront = CreateModel2D(L"obstacleTemplateFlappy.bmp");
    if (obstacle7FlappyFront.texture == NULL)
        return false;
    obstacle7FlappyFront.x = 1360; obstacle7FlappyFront.y = -500;

    obstacle8Flappy = CreateModel2D(L"obstacleBehindTemplateFlappy.bmp");
    if (obstacle8Flappy.texture == NULL)
        return false;
    obstacle8Flappy.x = 1410; obstacle8Flappy.y = 433;

    obstacle8FlappyFront = CreateModel2D(L"obstacleTemplateFlappy.bmp");
    if (obstacle8FlappyFront.texture == NULL)
        return false;
    obstacle8FlappyFront.x = 1360; obstacle8FlappyFront.y = 413;

    ///////////5TH LINE////////////
    obstacle9Flappy = CreateModel2D(L"obstacleBehindTemplateFlappy.bmp");
    if (obstacle5Flappy.texture == NULL)
        return false;
    obstacle9Flappy.x = 1710; obstacle9Flappy.y = -625;

    obstacle9FlappyFront = CreateModel2D(L"obstacleTemplateFlappy.bmp");
    if (obstacle5FlappyFront.texture == NULL)
        return false;
    obstacle9FlappyFront.x = 1660; obstacle9FlappyFront.y = -585;

    obstacle10Flappy = CreateModel2D(L"obstacleBehindTemplateFlappy.bmp");
    if (obstacle10Flappy.texture == NULL)
        return false;
    obstacle10Flappy.x = 1710; obstacle10Flappy.y = 373;

    obstacle10FlappyFront = CreateModel2D(L"obstacleTemplateFlappy.bmp");
    if (obstacle10FlappyFront.texture == NULL)
        return false;
    obstacle10FlappyFront.x = 1660; obstacle10FlappyFront.y = 353;

    ///////////6TH LINE////////////
    obstacle11Flappy = CreateModel2D(L"obstacleBehindTemplateFlappy.bmp");
    if (obstacle11Flappy.texture == NULL)
        return false;
    obstacle11Flappy.x = 2010; obstacle11Flappy.y = -425;

    obstacle11FlappyFront = CreateModel2D(L"obstacleTemplateFlappy.bmp");
    if (obstacle3FlappyFront.texture == NULL)
        return false;
    obstacle11FlappyFront.x = 1960; obstacle11FlappyFront.y = -385;

    obstacle12Flappy = CreateModel2D(L"obstacleBehindTemplateFlappy.bmp");
    if (obstacle12Flappy.texture == NULL)
        return false;
    obstacle12Flappy.x = 2010; obstacle12Flappy.y = 568;

    obstacle12FlappyFront = CreateModel2D(L"obstacleTemplateFlappy.bmp");
    if (obstacle12FlappyFront.texture == NULL)
        return false;
    obstacle12FlappyFront.x = 1960; obstacle12FlappyFront.y = 548;

    ///////////7TH LINE////////////
    obstacle13Flappy = CreateModel2D(L"obstacleBehindTemplateFlappy.bmp");
    if (obstacle13Flappy.texture == NULL)
        return false;
    obstacle13Flappy.x = 2310; obstacle13Flappy.y = -550;

    obstacle13FlappyFront = CreateModel2D(L"obstacleTemplateFlappy.bmp");
    if (obstacle13FlappyFront.texture == NULL)
        return false;
    obstacle13FlappyFront.x = 2260; obstacle13FlappyFront.y = -500;

    obstacle14Flappy = CreateModel2D(L"obstacleBehindTemplateFlappy.bmp");
    if (obstacle14Flappy.texture == NULL)
        return false;
    obstacle14Flappy.x = 2310; obstacle14Flappy.y = 433;

    obstacle14FlappyFront = CreateModel2D(L"obstacleTemplateFlappy.bmp");
    if (obstacle14FlappyFront.texture == NULL)
        return false;
    obstacle14FlappyFront.x = 2260; obstacle14FlappyFront.y = 413;

    ///////////8TH LINE////////////
    obstacle15Flappy = CreateModel2D(L"obstacleBehindTemplateFlappy.bmp");
    if (obstacle15Flappy.texture == NULL)
        return false;
    obstacle15Flappy.x = 2610; obstacle15Flappy.y = -675;

    obstacle15FlappyFront = CreateModel2D(L"obstacleTemplateFlappy.bmp");
    if (obstacle15FlappyFront.texture == NULL)
        return false;
    obstacle15FlappyFront.x = 2560; obstacle15FlappyFront.y = -635;

    obstacle16Flappy = CreateModel2D(L"Obstacle16_flappy_behind.bmp");
    if (obstacle16Flappy.texture == NULL)
        return false;
    obstacle16Flappy.x = 2610; obstacle16Flappy.y = 323;

    obstacle16FlappyFront = CreateModel2D(L"obstacleTemplateFlappy.bmp");
    if (obstacle16FlappyFront.texture == NULL)
        return false;
    obstacle16FlappyFront.x = 2560; obstacle16FlappyFront.y = 303;

    ///////////9TH LINE////////////
    obstacle17Flappy = CreateModel2D(L"obstacleBehindTemplateFlappy.bmp");
    if (obstacle17Flappy.texture == NULL)
        return false;
    obstacle17Flappy.x = 2910; obstacle17Flappy.y = -475;

    obstacle17FlappyFront = CreateModel2D(L"obstacleTemplateFlappy.bmp");
    if (obstacle17FlappyFront.texture == NULL)
        return false;
    obstacle17FlappyFront.x = 2860; obstacle17FlappyFront.y = -435;

    obstacle18Flappy = CreateModel2D(L"Obstacle16_flappy_behind.bmp");
    if (obstacle18Flappy.texture == NULL)
        return false;
    obstacle18Flappy.x = 2910; obstacle18Flappy.y = 518;

    obstacle18FlappyFront = CreateModel2D(L"obstacleTemplateFlappy.bmp");
    if (obstacle18FlappyFront.texture == NULL)
        return false;
    obstacle18FlappyFront.x = 2860; obstacle18FlappyFront.y = 498;

    ///////////10TH LINE////////////
    obstacle19Flappy = CreateModel2D(L"obstacleBehindTemplateFlappy.bmp");
    if (obstacle19Flappy.texture == NULL)
        return false;
    obstacle19Flappy.x = 3210; obstacle19Flappy.y = -375;

    obstacle19FlappyFront = CreateModel2D(L"obstacleTemplateFlappy.bmp");
    if (obstacle19FlappyFront.texture == NULL)
        return false;
    obstacle19FlappyFront.x = 3160; obstacle19FlappyFront.y = -335;

    obstacle20Flappy = CreateModel2D(L"obstacleBehindTemplateFlappy.bmp");
    if (obstacle20Flappy.texture == NULL)
        return false;
    obstacle20Flappy.x = 3210; obstacle20Flappy.y = 618;

    obstacle20FlappyFront = CreateModel2D(L"obstacleTemplateFlappy.bmp");
    if (obstacle20FlappyFront.texture == NULL)
        return false;
    obstacle20FlappyFront.x = 3160; obstacle20FlappyFront.y = 598;
    ///////////11TH LINE////////////
    obstacle21Flappy = CreateModel2D(L"obstacleBehindTemplateFlappy.bmp");
    if (obstacle21Flappy.texture == NULL)
        return false;
    obstacle21Flappy.x = 3510; obstacle21Flappy.y = -625;

    obstacle21FlappyFront = CreateModel2D(L"obstacleTemplateFlappy.bmp");
    if (obstacle21FlappyFront.texture == NULL)
        return false;
    obstacle21FlappyFront.x = 3460; obstacle21FlappyFront.y = -585;

    obstacle22Flappy = CreateModel2D(L"obstacleBehindTemplateFlappy.bmp");
    if (obstacle22Flappy.texture == NULL)
        return false;
    obstacle22Flappy.x = 3510; obstacle22Flappy.y = 373;

    obstacle22FlappyFront = CreateModel2D(L"obstacleTemplateFlappy.bmp");
    if (obstacle22FlappyFront.texture == NULL)
        return false;
    obstacle22FlappyFront.x = 3460; obstacle22FlappyFront.y = 353;

    ///////////12TH LINE////////////
    obstacle23Flappy = CreateModel2D(L"obstacleBehindTemplateFlappy.bmp");
    if (obstacle23Flappy.texture == NULL)
        return false;
    obstacle23Flappy.x = 3810; obstacle23Flappy.y = -425;

    obstacle23FlappyFront = CreateModel2D(L"obstacleTemplateFlappy.bmp");
    if (obstacle23FlappyFront.texture == NULL)
        return false;
    obstacle23FlappyFront.x = 3760; obstacle23FlappyFront.y = -385;

    obstacle24Flappy = CreateModel2D(L"obstacleBehindTemplateFlappy.bmp");
    if (obstacle24Flappy.texture == NULL)
        return false;
    obstacle24Flappy.x = 3810; obstacle24Flappy.y = 568;

    obstacle24FlappyFront = CreateModel2D(L"obstacleTemplateFlappy.bmp");
    if (obstacle24FlappyFront.texture == NULL)
        return false;
    obstacle24FlappyFront.x = 3760; obstacle24FlappyFront.y = 548;

    ///////////13TH LINE////////////
    obstacle25Flappy = CreateModel2D(L"obstacleBehindTemplateFlappy.bmp");
    if (obstacle25Flappy.texture == NULL)
        return false;
    obstacle25Flappy.x = 4110; obstacle25Flappy.y = -550;

    obstacle25FlappyFront = CreateModel2D(L"obstacleTemplateFlappy.bmp");
    if (obstacle25FlappyFront.texture == NULL)
        return false;
    obstacle25FlappyFront.x = 4060; obstacle25FlappyFront.y = -500;

    obstacle26Flappy = CreateModel2D(L"obstacleBehindTemplateFlappy.bmp");
    if (obstacle26Flappy.texture == NULL)
        return false;
    obstacle26Flappy.x = 4110; obstacle26Flappy.y = 433;

    obstacle26FlappyFront = CreateModel2D(L"obstacleTemplateFlappy.bmp");
    if (obstacle26FlappyFront.texture == NULL)
        return false;
    obstacle26FlappyFront.x = 4060; obstacle26FlappyFront.y = 413;

    ///////////14TH LINE////////////
    obstacle27Flappy = CreateModel2D(L"obstacleBehindTemplateFlappy.bmp");
    if (obstacle27Flappy.texture == NULL)
        return false;
    obstacle27Flappy.x = 4410; obstacle27Flappy.y = -500;

    obstacle27FlappyFront = CreateModel2D(L"obstacleTemplateFlappy.bmp");
    if (obstacle27FlappyFront.texture == NULL)
        return false;
    obstacle27FlappyFront.x = 4360; obstacle27FlappyFront.y = -450;

    obstacle28Flappy = CreateModel2D(L"obstacleBehindTemplateFlappy.bmp");
    if (obstacle28Flappy.texture == NULL)
        return false;
    obstacle28Flappy.x = 4410; obstacle28Flappy.y = 483;

    obstacle28FlappyFront = CreateModel2D(L"obstacleTemplateFlappy.bmp");
    if (obstacle28FlappyFront.texture == NULL)
        return false;
    obstacle28FlappyFront.x = 4360; obstacle28FlappyFront.y = 463;

    //SOUNDS
    soundEffect = LoadSound(L"background sound.WAV");
    if (soundEffect == NULL)
        return false;
    effectInstance = soundEffect->CreateInstance();

    duck = LoadSound(L"Pato Sound.WAV");
    if (soundEffect == NULL)
        return false;

    jumpingFlappy = LoadSound(L"jumpingsound.wav");
    if (soundEffect == NULL)
        return false;

    crash = LoadSound(L"CrashSound.wav");
    if (soundEffect == NULL)
        return false;

    //TEXT
    try {
        spriteFont = std::make_unique<SpriteFont>(dev,L"times_new_roman.spritefont");
    }
    catch (std::runtime_error e)
    {
        MessageBox(NULL, L"Loading times_new_roman.spritefont error", L"Error", MB_OK | MB_ICONERROR);
        return false;
    }

    return true;
}
void Game_Run()
{
    long static start = 0;
    float frame_interval = 1000.0 / framerate;
    if (GetCursorPos(&p))
    {
        //cursor position now in p.x and p.y
    }

    if (keyboard->GetState().Escape)
        gameover = true;

    if (GetTickCount() - start >= frame_interval)
    {
        //reset timing
        start = GetTickCount();
        ClearScreen();

        spriteBatch->Begin();

        // draw background
        RECT game_window;
        game_window.left = skater.x - Width / 2;
       ;
        if (game_window.left < 0)
            game_window.left = 0;
        if (game_window.left > world_width - Width)
            game_window.left = world_width - Width;
        game_window.top = skater.y - Height / 2;
        if (game_window.top < 0)
            game_window.top = 0;
        if (game_window.top > world_height - Height)
            game_window.top = world_height - Height;
        game_window.right = game_window.left + Width;
        game_window.bottom = game_window.top + Height;

        if (menuflag == 1 )
        {
            DrawModel2D(mainmenu, game_window);
        
        if (p.y < 425 && p.y > 295 && p.x < 710 && p.x > 300 && mouse->GetState().leftButton && menuflag==1 )
        {
            menuflag = 0;
            menulevelsflag = 1;
            game_flag = 0;
            game_state = 0;
        }
        }
        if (menulevelsflag == 1)
        {
            DrawModel2D(menulevels, game_window);
            if (skater.x <= 400)
            {
                score = 0;
            }
            if (score > highscore1)
            {
                highscore1 = score;
            }
            wchar_t s[80];
            swprintf(s, 80, L"HIGHSCORE=%d", highscore1);
            spriteFont->DrawString(spriteBatch.get(), s, XMFLOAT2(600, 100), Colors::Red);

            
            if (score3 > highscore2)
            {
                highscore2 = score3;
            }
            swprintf(s, 80, L"HIGHSCORE=%d", highscore2);
            spriteFont->DrawString(spriteBatch.get(), s, XMFLOAT2(600, 530), Colors::Red);
        }
        //OPEN GAME1
        if (p.y < 265 && p.y > 50 && p.x < 630 && p.x > 100 && mouse->GetState().leftButton && menulevelsflag==1 )
        {
            menuflag = 0;
            game_flag = 1;
            game2_flag = 0;
            game_state = 1;
            menulevelsflag = 0;
            effectInstance->Play(true);
        }
        //RESETHIGHSCORE1
        if (p.y < 205 && p.y > 165 && p.x < 800 && p.x > 670 && mouse->GetState().leftButton && menulevelsflag == 1)
        {
            highscore1=0;
        }
        //HOWTOPLAY1
        if (p.y < 265 && p.y > 225 && p.x < 900 && p.x > 670 && mouse->GetState().leftButton && menulevelsflag == 1)
        {
            wchar_t message[600];
            swprintf(message, 600, L"Left or Right to move sideways, no need to stay pressing, the skater is always moving. Spacebar to jump, you don't need to hold the button.  What makes you lose: 2  flying ducks and spikes on the flor, watch out for those! The brown boxes will not make you lose.", score);
            MessageBox(NULL, message, L"HOW TO PLAY GAME 1", MB_OK);
        }
        //OPEN GAME2
        if (p.y < 690 && p.y > 490 && p.x < 615 && p.x > 100 && mouse->GetState().leftButton && menulevelsflag == 1)
        {
            menuflag = 0;
            game_flag = 0;
            game2_flag = 1;
            game2_state = 1;
            menulevelsflag = 0;
        }
        //RESETHIGHSCORE2
        if (p.y < 640 && p.y > 600 && p.x < 800 && p.x > 670 && mouse->GetState().leftButton && menulevelsflag == 1)
        {
            score3 = 0;
            highscore2 = 0;
        }
        //HOWTOPLAY2
        if (p.y < 700 && p.y > 660 && p.x < 900 && p.x > 670 && mouse->GetState().leftButton && menulevelsflag == 1)
        {
            wchar_t message[600];
            swprintf(message, 600, L"Space bar to jump. Avoid the green pipes!", score);
            MessageBox(NULL, message, L"HOW TO PLAY GAME 1", MB_OK);
        }
        if (game_flag == 1)
        {
            DrawModel2D(background, game_window);

            UpdateSkater();
            DrawModel2D(skater, game_window);
            DrawModel2D(obstacle1_1, game_window);
            DrawModel2D(obstacle2_2, game_window);
            DrawModel2D(obstacle3_3, game_window);
            DrawModel2D(obstacle4_4, game_window);
            DrawModel2D(obstacle5_5, game_window);

            DrawModel2D(spikes2, game_window);   
            DrawModel2D(spikes3, game_window);    
            DrawModel2D(spikes4, game_window);  
            DrawModel2D(spikes5, game_window);
            DrawModel2D(spikes6, game_window);
            DrawModel2D(spikes7, game_window);
            
            UpdateDuckBehind1();
            UpdateDuck1();
            DrawModel2D(duck1, game_window);
            
            UpdateDuckBehind2();
            UpdateDuck2();
            DrawModel2D(duck2, game_window);

            score = skater.x * 100 / 4486;
            if (score <= 8)
            {
                score = 0;
            }
            if (skater.x > 400)
            {
                wchar_t s[80];
                swprintf(s, 80, L"SCORE=%d", score);
                spriteFont->DrawString(spriteBatch.get(), s, XMFLOAT2(50, 50), Colors::Red);
            }

        }
       
        if (game2_flag == 1)
        {
            // draw background
            RECT game_window;
            
            game_window.left = skaterFlappy.x - Width / 2;
            if (game_window.left < 0)
                game_window.left = 0;
            if (game_window.left > world_width - Width)
                game_window.left = world_width - Width;
            game_window.top = skaterFlappy.y - Height / 2;
            if (game_window.top < 0)
                game_window.top = 0;
            if (game_window.top > world_height - Height)
                game_window.top = world_height - Height;
            game_window.right = game_window.left + Width;
            game_window.bottom = game_window.top + Height;

            DrawModel2D(backgroundGame2, game_window);
            
            DrawModel2D(obstacle1FlappyFront, game_window);
            DrawModel2D(obstacle2FlappyFront, game_window);            
            DrawModel2D(obstacle3FlappyFront, game_window);            
            DrawModel2D(obstacle4FlappyFront, game_window);            
            DrawModel2D(obstacle5FlappyFront, game_window);            
            DrawModel2D(obstacle6FlappyFront, game_window);            
            DrawModel2D(obstacle7FlappyFront, game_window);           
            DrawModel2D(obstacle8FlappyFront, game_window);           
            DrawModel2D(obstacle9FlappyFront, game_window);           
            DrawModel2D(obstacle10FlappyFront, game_window);          
            DrawModel2D(obstacle11FlappyFront, game_window);           
            DrawModel2D(obstacle12FlappyFront, game_window);           
            DrawModel2D(obstacle13FlappyFront, game_window);           
            DrawModel2D(obstacle14FlappyFront, game_window);           
            DrawModel2D(obstacle15FlappyFront, game_window);           
            DrawModel2D(obstacle16FlappyFront, game_window);           
            DrawModel2D(obstacle17FlappyFront, game_window);          
            DrawModel2D(obstacle18FlappyFront, game_window);          
            DrawModel2D(obstacle19FlappyFront, game_window);          
            DrawModel2D(obstacle20FlappyFront, game_window);            
            DrawModel2D(obstacle21FlappyFront, game_window);          
            DrawModel2D(obstacle22FlappyFront, game_window);
            DrawModel2D(obstacle23FlappyFront, game_window);
            DrawModel2D(obstacle24FlappyFront, game_window);
            DrawModel2D(obstacle25FlappyFront, game_window);  
            DrawModel2D(obstacle26FlappyFront, game_window);
            DrawModel2D(obstacle27FlappyFront, game_window);
            DrawModel2D(obstacle28FlappyFront, game_window);

            UpdateSkaterFlappy();
            DrawModel2D(skaterFlappy, game_window);
            UpdateScore();
            wchar_t s[80];
            swprintf(s, 80, L"SCORE=%d", score3);
            spriteFont->DrawString(spriteBatch.get(), s, XMFLOAT2(50, 50), Colors::Red);
        }

        spriteBatch->End();
        swapchain->Present(0, 0);

    }
}

void Game_End()
{
    soundEffect.release();
    mainmenu.texture->Release();
    skater.texture->Release();
    background.texture->Release();
    obstacle1.texture->Release();
    obstacle1_1.texture->Release();
    obstacle2.texture->Release();
    obstacle2_2.texture->Release();

    
    CleanD3D();
}


void UpdateSkater()
{
    if (game_state == 0) // game is paused
    {
        game_flag = 0;  //make it go back to main menu
        menulevelsflag = 1;
        skater.x = Width / 2;
        skater.y = road_pos;
    }
    else {
        
        auto kb = keyboard->GetState();
        
        if (kb.Left)
        {
            skater.move_x = -skater_speed;
            skater.frame = 0;
        }
        if (kb.Right)
        {
            skater.move_x = skater_speed;
            skater.frame = 1;
        }
        if (kb.Space)
        {
            if (skater.y >200)
            {
                if (goingdown == 0) // player can only order to jump when skater is in the ground
                {
                    jump = 10;
                }
            }
        }
        if (skater.x < Width / 2)
        {
            skater.x = Width / 2;
            
            skater.frame = 1;
        }
        skater.x += skater.move_x;
        skater.y -= jump;                    // y positive direction is downward
        if (skater.y < 200)                  // reached the highest point
        {           
            goingdown = 1;
            jump = -10;
        }
        if (skater.y >= road_pos)            // if underground
        {
            jump = 0;
            skater.y = road_pos;
            goingdown = 0;
        }
        if (skater.x < 0)            // if outside of the window
        {
            skater.x = 0;
        }
        if (skater.x < 740 && skater.y == 223 || skater.x > 950 && skater.x<1350 && skater.y == 223)     //fall after droping frpom obstacle1
        {
            jump = -10;
            goingdown = 1;
        }
        if (skater.x > 1530 && skater.x <1600 && skater.y == 223)     //fall after droping frpom obstacle2
        {
            jump = -10;
            goingdown = 1;
        }
        if (skater.x > 1760 && skater.x < 2350 && skater.y == 223)     //fall after droping frpom obstacle3
        {
            jump = -10;
            goingdown = 1;
        }
        if (skater.x > 2510 && skater.x < 3150 && skater.y == 223)     //fall after droping frpom obstacle4
        {
            jump = -10;
            goingdown = 1;
        }
        if (skater.x > 3284  && skater.y == 223)     //fall after droping frpom obstacle5
        {
            jump = -10;
            goingdown = 1;
        }
    }
   
   if (CheckModel2DCollided(skater, obstacle1))
   {
       skater.x -= skater.move_x;
       skater.y -= skater.move_y;
        if (skater.x > 740 && skater.x < 950 && skater.y + skater.frame_height / 2 >= obstacle1.y - 100)
        {
        skater.y = 223;
        jump = 0;
        goingdown = 0;
        }
   }
   if (CheckModel2DCollided(skater, obstacle2))
   {
       skater.x -= skater.move_x;
       skater.y -= skater.move_y;
       if (skater.x > 1350 && skater.x < 1530 && skater.y + skater.frame_height / 2 >= obstacle2.y - 100)
       {
           skater.y = 223;
           jump = 0;
           goingdown = 0;
       }
   }
   if (CheckModel2DCollided(skater, obstacle3))
   {
       skater.x -= skater.move_x;
       skater.y -= skater.move_y;
       if (skater.x > 1600 && skater.x < 1760 && skater.y + skater.frame_height / 2 >= obstacle2.y - 100)
       {
           skater.y = 223;
           jump = 0;
           goingdown = 0;
       }

   }
   if (CheckModel2DCollided(skater, obstacle4))
   {
       skater.x -= skater.move_x;
       skater.y -= skater.move_y;
       if (skater.x > 2350 && skater.x < 2510 && skater.y + skater.frame_height / 2 >= obstacle2.y - 100)
       {
           skater.y = 223;
           jump = 0;
           goingdown = 0;
       }
   }
   if (CheckModel2DCollided(skater, obstacle5))
   {
       skater.x -= skater.move_x;
       skater.y -= skater.move_y;
       if (skater.x > 3150 && skater.x < 3310 && skater.y + skater.frame_height / 2 >= obstacle2.y - 100)
       {
           skater.y = 223;
           jump = 0;
           goingdown = 0;
       }
   }
   if (CheckModel2DCollided(skater, ball2))
   {
       skater.x -= skater.move_x;
       skater.y -= skater.move_y;
       game_state = 0;
       duckbehind1.x = 4600;
       duck1.x = 4550;
       duckbehind2.x = 1800;
       duck2.x = 1750;
       if (score > highscore1)
       {
           highscore1 = score;
       }
       effectInstance->Stop();
       wchar_t message[80];
       swprintf(message, 80, L"SCORE = %d", score);
       MessageBox(NULL, message, L"YOU LOST", MB_OK);
       skater.move_x = 0;  skater.move_y = 0;
       skater.frame = 1;
       //mainmenu.x = 18;
       //mainmenu.y = 0;
   }
   if (CheckModel2DCollided(skater, ball3))
   {
       skater.x -= skater.move_x;
       skater.y -= skater.move_y;
       game_state = 0;
       duckbehind1.x = 4600;
       duck1.x = 4550;
       duckbehind2.x = 1800;
       duck2.x = 1750;
       if (score > highscore1)
       {
           highscore1 = score;
       }
       effectInstance->Stop();
       wchar_t message[80];
       swprintf(message, 80, L"SCORE = %d", score);
       MessageBox(NULL, message, L"YOU LOST", MB_OK);
       skater.move_x = 0;  skater.move_y = 0;
       skater.frame = 1;
       //mainmenu.x = 18;
       //mainmenu.y = 0;
   }
   if (CheckModel2DCollided(skater, ball4))
   {
       skater.x -= skater.move_x;
       skater.y -= skater.move_y;
       game_state = 0;
       duckbehind1.x = 4600;
       duck1.x = 4550;
       duckbehind2.x = 1800;
       duck2.x = 1750;
       if (score > highscore1)
       {
           highscore1 = score;
       }
       effectInstance->Stop();
       wchar_t message[80];
       swprintf(message, 80, L"SCORE = %d", score);
       MessageBox(NULL, message, L"YOU LOST", MB_OK);
       skater.move_x = 0;  skater.move_y = 0;
       skater.frame = 1;
       //mainmenu.x = 18;
       //mainmenu.y = 0;
   }
   if (CheckModel2DCollided(skater, ball5))
   {
       skater.x -= skater.move_x;
       skater.y -= skater.move_y;
       game_state = 0;
       duckbehind1.x = 4600;
       duck1.x = 4550;
       duckbehind2.x = 1800;
       duck2.x = 1750;
       if (score > highscore1)
       {
           highscore1 = score;
       }
       effectInstance->Stop();
       wchar_t message[80];
       swprintf(message, 80, L"SCORE = %d", score);
       MessageBox(NULL, message, L"YOU LOST", MB_OK);
       skater.move_x = 0;  skater.move_y = 0;
       skater.frame = 1;
       //mainmenu.x = 18;
       //mainmenu.y = 0;
   }
   if (CheckModel2DCollided(skater, ball6))
   {
       skater.x -= skater.move_x;
       skater.y -= skater.move_y;
       game_state = 0;
       duckbehind1.x = 4600;
       duck1.x = 4550;
       duckbehind2.x = 1800;
       duck2.x = 1750;
       if (score > highscore1)
       {
           highscore1 = score;
       }
       effectInstance->Stop();
       wchar_t message[80];
       swprintf(message, 80, L"SCORE = %d", score);
       MessageBox(NULL, message, L"YOU LOST", MB_OK);
       skater.move_x = 0;  skater.move_y = 0;
       skater.frame = 1;
       //mainmenu.x = 18;
       //mainmenu.y = 0;
   }
   if (CheckModel2DCollided(skater, ball7))
   {
       skater.x -= skater.move_x;
       skater.y -= skater.move_y;
       game_state = 0;
       duckbehind1.x = 4600;
       duck1.x = 4550;
       duckbehind2.x = 1800;
       duck2.x = 1750;
       if (score > highscore1)
       {
           highscore1 = score;
       }
       effectInstance->Stop();
       wchar_t message[80];
       swprintf(message, 80, L"SCORE = %d", score);
       MessageBox(NULL, message, L"YOU LOST", MB_OK);
       skater.move_x = 0;  skater.move_y = 0;
       skater.frame = 1;
       //mainmenu.x = 18;
       //mainmenu.y = 0;
   }
    if (skater.x > 4500 ) 
    {
        game_state = 0;
        duckbehind1.x = 4600;
        duck1.x = 4550;
        duckbehind2.x = 1800;
        duck2.x = 1750;
        if (score > highscore1)
        {
            highscore1 = score;
        }
        effectInstance->Stop();
        wchar_t message[80];
        swprintf(message, 80, L"SCORE = %d", score);
        MessageBox(NULL, message, L"YOU WON CONGRATULATIONS!!!", MB_OK);
        skater.move_x = 0;  skater.move_y = 0;
        //mainmenu.x = 18;
        //mainmenu.y = 0;
    }
}
void UpdateDuckBehind1()
{
    duckbehind1.frame++;
    duckbehind1.x += duckbehind1.move_x;
    if (duckbehind1.x < 50)
    {
        duckbehind1.x = 4600;
    }
    if (CheckModel2DCollided(skater, duckbehind1))
    {
        duckbehind1.x -= duckbehind1.move_x;
        duckbehind1.y -= duckbehind1.move_y;
        duckbehind1.x = 4600;
        duck1.x = 4550;
        duckbehind2.x = 1800;
        duck2.x = 1750;
        game_state = 0;
        if (score > highscore1)
        {
            highscore1 = score;
        }
        PlaySound(duck.get());
        effectInstance->Stop();
        wchar_t message[80];
        swprintf(message, 80, L"SCORE = %d", score);
        MessageBox(NULL, message, L"YOU LOST", MB_OK);
        skater.move_x = 0;  skater.move_y = 0;
        //mainmenu.x = 18;
        //mainmenu.y = 0;
    }
}
void UpdateDuck1()
{
    duck1.frame++;
    duck1.x += duck1.move_x;
    if (duck1.x < 0)
    {
        duck1.x = 4550;
    }
}
void UpdateDuckBehind2()
{
    duckbehind2.frame++;
    duckbehind2.x += duckbehind2.move_x;
    if (duckbehind2.x < 50)
    {
        duckbehind2.x = 4600;
    }
    if (CheckModel2DCollided(skater, duckbehind2))
    {
        duckbehind2.x -= duckbehind2.move_x;
        duckbehind2.y -= duckbehind2.move_y;
        duckbehind1.x = 4600;
        duck1.x = 4550;
        duckbehind2.x = 1800;
        duck2.x = 1750;
        game_state = 0;
        PlaySound(duck.get());
        if (score > highscore1)
        {
            highscore1 = score;
        }
        effectInstance->Stop();
        wchar_t message[80];
        swprintf(message, 80, L"SCORE = %d", score);
        MessageBox(NULL, message, L"YOU LOST", MB_OK);
        skater.move_x = 0;  skater.move_y = 0;
        //mainmenu.x = 18;
        //mainmenu.y = 0;
    }
}
void UpdateDuck2()
{
    duck2.frame++;
    duck2.x += duck2.move_x;
    if (duck2.x < 0)
    {
        duck2.x = 4550;
    }
}

void UpdateSkaterFlappy()
{
    if (game2_state == 0) // game is paused
    {
        game2_flag = 0;  //make it go back to main menu
        menulevelsflag = 1;
        skaterFlappy.x = 50;
        skaterFlappy.y = road_pos;

    }
    else {
        
        jump = -5;
        auto kb = keyboard->GetState();
        if (kb.Space)
        {
            //PlaySound(jumpingFlappy.get());
            jump = 30;
        }
        if (skaterFlappy.y <300 && skaterFlappy.x<100 )// When game starts with this "if" the skater will go down even if the last move before losing was going up
        {
            
            skaterFlappy.y = 300;
            skaterFlappy.x -= skaterFlappy.move_x;

        }
        skaterFlappy.x += skaterFlappy.move_x;
        skaterFlappy.y -= jump;                    // y positive direction is downward
        if (skaterFlappy.y < 0)
        {
            game2_state = 0;
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (skaterFlappy.y > 708)
        {
            game2_state = 0;
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle1Flappy))
        {
            game2_state = 0;
            score3 = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle2Flappy))
        {
            game2_state = 0;
            score3 = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle3Flappy))
        {
            game2_state = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle4Flappy))
        {
            game2_state = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle5Flappy))
        {
            game2_state = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle6Flappy))
        {
            game2_state = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle7Flappy))
        {
            game2_state = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle8Flappy))
        {
            game2_state = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle9Flappy))
        {
            game2_state = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle10Flappy))
        {
            game2_state = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle11Flappy))
        {
            game2_state = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle12Flappy))
        {
            game2_state = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle13Flappy))
        {
            game2_state = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle14Flappy))
        {
            game2_state = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle15Flappy))
        {
            game2_state = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle16Flappy))
        {
            game2_state = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle17Flappy))
        {
            game2_state = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle18Flappy))
        {
            game2_state = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle19Flappy))
        {
            game2_state = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle20Flappy))
        {
            game2_state = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle21Flappy))
        {
            game2_state = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle22Flappy))
        {
            game2_state = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle23Flappy))
        {
            game2_state = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle24Flappy))
        {
            game2_state = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle25Flappy))
        {
            game2_state = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle26Flappy))
        {
            game2_state = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle27Flappy))
        {
            game2_state = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (CheckModel2DCollided(skaterFlappy, obstacle28Flappy))
        {
            game2_state = 0;
            PlaySound(crash.get());
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"YOU LOST", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
        if (skaterFlappy.x > 4500)
        {
            game2_state = 0;
            wchar_t message[80];
            swprintf(message, 80, L"SCORE=%d", score3);
            MessageBox(NULL, message, L"CONGRATULATIONS YOU WON!!", MB_OK);
            skaterFlappy.move_y = 0;
            //mainmenu.x = 18;
            //mainmenu.y = 0;
        }
    }
}
void UpdateScore()
{
    if (skaterFlappy.x > 617)
    {
        score3 = 1;
    }
    if (skaterFlappy.x > 917)
    {
        score3 = 2;
    }
    if (skaterFlappy.x > 1217)
    {
        score3 = 3;
    }
    if (skaterFlappy.x > 1517)
    {
        score3 = 4;
    }
    if (skaterFlappy.x > 1817)
    {
        score3 = 5;
    }
    if (skaterFlappy.x > 2117)
    {
        score3 = 6;
    }
    if (skaterFlappy.x > 2417)
    {
        score3 = 7;
    }
    if (skaterFlappy.x > 2717)
    {
        score3 = 8;
    }
    if (skaterFlappy.x > 3017)
    {
        score3 = 9;
    }
    if (skaterFlappy.x > 3317)
    {
        score3 = 10;
    }
    if (skaterFlappy.x > 3617)
    {
        score3 = 11;
    }
    if (skaterFlappy.x > 3917)
    {
        score3 = 12;
    }
    if (skaterFlappy.x > 4217)
    {
        score3 = 13;
    }
    if (skaterFlappy.x > 4500)
    {
        score3 = 14;
    }
    if (skaterFlappy.x > 50 && skaterFlappy.x< 617)
    {
        score3 = 0;
    }
}