#define WIDTH 1200
#define HEIGHT 600
#define SCORE_SECTION 50

#define BALL_NUM 22
#define FORCE_LIMIT 800.f
#define FRICTION -0.4f

#define RED_X (WIDTH/2 - 250.f)
#define RED_Y (HEIGHT/2.f)

#define BLUE_X (WIDTH/2.f)
#define BLUE_Y (HEIGHT/2.f)

#define BLACK_X 150.f
#define BLACK_Y (HEIGHT/2.f)

#define ORANGE_X (WIDTH - 300.f)
#define ORANGE_Y (HEIGHT/2.f)

#define YELLOW_X (WIDTH - 300.f)
#define YELLOW_Y (HEIGHT/3.f * 2.f)

#define GREEN_X (WIDTH - 300.f)
#define GREEN_Y (HEIGHT/3.f)

#define RADIUS 10.3125f
#define POCKET_RADIUS 15.f
#define D_ZONE_RADIUS (YELLOW_Y - ORANGE_Y)

#define DEG2RAD(x) ((x) * (M_PI/180.0f))