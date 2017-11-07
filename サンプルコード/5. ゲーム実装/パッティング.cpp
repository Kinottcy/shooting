#include "Game.hpp"

int step;

int mapValue[20][20];
int gt[4][2];
int score[10];
int hole;
int bx;
int by;
int cx;
int cy;
float mx;
float my;
int shot;
float angle;
float power;
float powerSpeed;

string mapData[9][24] = {
    // Hole 1
    {
        "55444333223456789ABC", "444333221123456789AB", "4333221111123456789A",
        "33221112211123456789", "22111123321112345678", "11111233432211234567",
        "11111234543321123456", "11111234332211112345", "11111123221111111234",
        "21111122111111111123", "32211111111111111112", "33322211111111111122",
        "44433322211111222233", "55544433322222333344", "66555544433333444455",
        "76666555544444555566", "77776666655555666677", "88877777766666777778",
        "99988888777777888888", "77776666655555666677", "48", "48", "248", "216"
    },
    // Hole 2
    {
        "7777654321368ABBBAAA", "77765432111368ABBAAA", "765432111111368AABBB",
        "54321111111113688AAA", "32111111111111366888", "42111111111111133666",
        "64211111111111111333", "96421111111111111111", "B9642111111111110000",
        "DB964211111100000000", "EDB96421111000000000", "FEDB9642111000000000",
        "FFEDB964211000000000", "FFFEDB96421000000000", "FFFEDB96421100000000",
        "FFFFEDB9642100000000", "FFFFEDB9642100000000", "EFFFEDB9642100000000",
        "CEFFEDB9642100000000", "CEFFEDB9642100000000", "248", "48", "64", "248"
    },
    // Hole 3
    {
        "00000023454320000000", "00000023454320000000", "00000023454320000000",
        "00000023454320000000", "00000023454320000000", "00000023454320000000",
        "22222223454322222222", "33333333454333333333", "44444444454444444444",
        "55555555555555555555", "44444444454444444444", "33333333454333333333",
        "22222223454322222222", "00000023454320000000", "00000023454320000000",
        "00000023454320000000", "00000023454320000000", "00000023454320000000",
        "00000023454320000000", "00000023454320000000", "144", "232", "232", "144"
    },
    // Hole 4
    {
        "FFFFFFC850058CFFFFFF", "FFFFFC85000058CFFFFF", "FFFFFC850000058CFFFF",
        "FFFFC85210001258CCFF", "FFFFC8521111112258CC", "FFFC8520001111112558",
        "FCC85200002222111225", "21111125552258852155", "85520000258888520000",
        "5221100255558B852005", "21111125552258852155", "10001125650000555555",
        "00000258850000022555", "0000058BC85500111255", "4000158C888521111255",
        "84111258855200012588", "FC41112552200002588B", "FF841112200000258BBB",
        "FFC4111100000258BDDD", "FFFC411110000258BDFF", "56", "232", "200", "72"
    },
    // Hole 5
    {
        "555544433300000068AC", "66665554443000068ACF", "7777666554400068ACFF",
        "7888777654430468ACFF", "678998765432468ACFFC", "567788765432468ACCCA",
        "55667765432468ACAAA8", "33556665432468AA8886", "0004565432468A886664",
        "00004454324688664441", "00000543246886441122", "75500023246864122244",
        "98765432468642244466", "A9876543246424466688", "BA987654324246888AAA",
        "CBA98765432468AAAAA7", "DCBA98765432468AAAA7", "EDCBA98765432468AA74",
        "FEDCBA98765432468A74", "FEDCBA98765432468A74", "232", "104", "56", "200"
    },
    // Hole 6
    {
        "00000000000000000000", "00011111000000000000", "00111111111111000000",
        "00111111111111111000", "00111110000111111100", "00011111000000111100",
        "00001111100001111000", "00000011111111110000", "11000000111111111000",
        "10000001111111111100", "00000111110001111100", "00011111100011111000",
        "00111110000111110000", "00111100001111100001", "00111100011111000011",
        "00111111111110000111", "00011111111000001111", "00001111000000011111",
        "00000000000001111111", "00000000001111111111", "88", "264", "72", "24"
    },
    // Hole 7
    {
        "235BEB53212358B85321", "1235B532121235853212", "21235321232123532123",
        "32123212353212321235", "53212123585321212358", "853212358B853212358B",
        "B8532358BEB8532358BE", "853212358B853212358B", "53212123585321212358",
        "32123212353212321235", "21235321232123532123", "12358532121235853212",
        "2358B853212358B85321", "358BEB8532358BEB8532", "2358B853212358B85321",
        "12358532121235853212", "21235321232123532123", "32123212353212321235",
        "53212123585321212358", "853212358B853212358B", "104", "264", "184", "40"
    },
    // Hole 8
    {
        "11111111111111100000", "11111111222111100000", "11111122444211110000",
        "11112444888421110000", "00012488AAA842111000", "00000248888222111000",
        "10002400000444211100", "12461000000048421111", "12460000000048842111",
        "12460000000224884211", "12460000022466488421", "11241002244664244442",
        "21121024466642122221", "A5111246688642111000", "DEA51246886421000000",
        "BDEA5124686420000000", "8BDEA512464200000000", "48BDEA51242000000000",
        "248BDEA5120000000000", "1248BDEA500000000000", "56", "56", "104", "264"
    },
    // Hole 9
    {
        "11111111111111111122", "11111111111111111244", "10000000111111112488",
        "000000000000111248AA", "00000000000002248AEE", "33330000000003248AEE",
        "4444444440003248AEEE", "5555500044444348AEEE", "6666600003344348AEEE",
        "88880000266833248AAE", "AAAA0002488A8322488A", "DDB800248AAEA8412448",
        "FFDB8248AEEEA8411224", "FFDB858AAAAA84111112", "FFDB8448888841111111",
        "FFFDB844444411111111", "FFFDB842222211111111", "FFFDB840000001111111",
        "FFFFDB00000000011111", "FFFFF000000000011111", "56", "104", "248", "248"
    },
};

Vector2 ConvertPoint(int x, int y)
{
    int a = int(mapValue[x/16][y/16] + (mapValue[x/16+1][y/16] - mapValue[x/16][y/16])/16.0f * (x % 16));
    int b = int(mapValue[x/16][y/16+1] + (mapValue[x/16+1][y/16+1] - mapValue[x/16][y/16+1])/16.0f * (x % 16));
    return Vector2(320 + x - y, 480-int(64 + (x + y) / 2 - (a + (b - a) / 16.0f * (y % 16))));
}

void LoadHoleData()
{
    for (int i = 0; i < 20; i++) {
        string& mapStr = mapData[hole%9][i];
        for (int j = 0; j < 20; j++) {
            if (mapStr.length() >= 20) {
                string str = mapStr.substr(j, 1);
                mapValue[j][i] = strtol(str.c_str(), NULL, 16) * 2;
            } else {
                mapValue[j][i] = 0;
            }
        }
    }
    bx = strtol(mapData[hole%9][20].c_str(), NULL, 10);
    by = strtol(mapData[hole%9][21].c_str(), NULL, 10);
    cx = strtol(mapData[hole%9][22].c_str(), NULL, 10);
    cy = strtol(mapData[hole%9][23].c_str(), NULL, 10);
    if (hole >= 9) {
        swap(bx, cx);
        swap(by, cy);
    }
    
    step = 1;
    power = 0.0f;
    powerSpeed = 2.0f;
    if (std::abs(bx - cx) > std::abs(by - cy)) {
        if (Mathf::Sign(bx - cx) == -1) {
            angle = 0.0f;
        } else {
            angle = M_PI;
        }
    } else {
        if (Mathf::Sign(by - cy) == -1) {
            angle = M_PI_2;
        } else {
            angle = M_PI / 2 * 3;
        }
    }
}

void Start()
{
    hole = 0;
    LoadHoleData();
    
    step = 1;
}

void DrawMap()
{
    for (int j = 1; j <= 18; j++) {
        for (int i = 1; i <= 17; i++) {
            // 奥の点
            Vector2 p1(320+i*16-j*16, 480-(64+i*8+j*8-mapValue[i][j]));
            // 右（上手）の点
            Vector2 p2(320+(i+1)*16-j*16, 480-(64+(i+1)*8+j*8-mapValue[i+1][j]));
            // 左（下手）の点
            Vector2 p3(320+i*16-(j+1)*16, 480-(64+(i+1)*8+j*8-mapValue[i][j+1]));
            // 手前の点
            Vector2 p4(320+(i+1)*16-(j+1)*16, 480-(64+(i+1)*8+(j+1)*8-mapValue[i+1][j+1]));
            
            // 奥行きと手前で角度を出す
            int angle = mapValue[i][j] - mapValue[i+1][j+1];
            if (angle == 0) {
                // 角度が0なら左と右で角度を出す
                angle = mapValue[i][j+1] - mapValue[i+1][j];
            }
            float light = (angle / 8.0f) + 0.5f;
            Color color = Color(0.0f, 0.75f+light*0.25f, 0.0f);
            if (mapValue[i][j] == 0 && mapValue[i+1][j] == 0 &&
                mapValue[i][j+1] == 0 && mapValue[i+1][j+1] == 0)
            {
                color = Color(0.2f, 0.2f, 1.0f);
            }
            FillTriangle(p1, p2, p3, color);
            FillTriangle(p2, p3, p4, color);
            DrawLine(p1, p2, Color::blue);
            DrawLine(p1, p3, Color::blue);
            DrawLine(p2, p4, Color::blue);
            DrawLine(p3, p4, Color::blue);
        }
    }
    FillCircle(ConvertPoint(cx, cy), { 3, 2 }, Color::black);
}

void DrawInfoTexts()
{
    for (int i = 0; i < 2; i++) {
        Color color = (i == 0)? Color::white: Color::black;
        FillRect(Rect(9+i, 480-(38-i), 126-i*2, 29-i*2), color);
        FillRect(Rect(9+i, 480-(86-i), 118-i*2, 45-i*2), color);
        FillRect(Rect(9+i, 480-(118-i), 150-i*2, 29-i*2), color);
    }
    
    SetFont("nicoca_v1.ttf", 24.0f);
    DrawText(FormatString("HOLE %d", hole+1), { 15, 445 }, Color::white);
    
    SetFont("nicoca_v1.ttf", 20.0f);
    DrawText(FormatString("SHOT: %d", shot), { 15, 417 }, Color::white);
    DrawText(FormatString("SCORE: %d", 0), { 15, 399 }, Color::white);
}

void DrawBall()
{
    Vector2 ballPos = ConvertPoint(bx, by);
    FillCircle(ballPos-Vector2(1, 1), 2.0f, Color::black.Alpha(0.8f));
    FillCircle(ballPos, 2.0f, Color::white);
}

void DrawTarget()
{
    float x = bx + cosf(angle) * 12;
    float y = by + sinf(angle) * 12;
    Vector2 targetPos = ConvertPoint(x, y);
    FillCircle(targetPos-Vector2(1, 1), 2.0f, Color::black.Alpha(0.8f));
    FillCircle(targetPos, 2.0f, Color(1.0f, 0.5f, 0.5f));
}

void DrawPower()
{
    FillRect(Rect(16, 480-111, power*32*4+3, 15), Color(1.0f, 0.5f, 0.5f));
}

void ProcessShot()
{
    Vector2 ballPos = ConvertPoint(bx, by);
    int xx = bx;
    int yy = by;
    int a = int(mapValue[xx/16][yy/16] + (mapValue[xx/16+1][yy/16] - mapValue[xx/16][yy/16])/16.0f * (xx % 16));
    int b = int(mapValue[xx/16][yy/16+1] + (mapValue[xx/16+1][yy/16+1] - mapValue[xx/16][yy/16+1])/16.0f * (xx % 16));
    int c = b - a;
    my -= c / 550.0f + my / 30;
    by += my;
    if (by < 16 || by > 287) {
        shot += 1;
        step = 1;
        return;
    }
    
    a = int(mapValue[xx/16][yy/16] + (mapValue[xx/16][yy/16+1] - mapValue[xx/16][yy/16])/16.0f * (yy % 16));
    b = int(mapValue[xx/16+1][yy/16] + (mapValue[xx/16+1][yy/16+1] - mapValue[xx/16+1][yy/16])/16.0f * (yy % 16));
    int d = b - a;
    mx -= d / 550.0f + mx / 30;
    bx += mx;
    if (bx < 16 || bx > 287) {
        shot += 1;
        power = 0;
        step = 1;
        return;
    }
    
    if (std::abs(cx - bx) < 2 && std::abs(cy - by) < 1) {
        printf("In!! %f,%f\n", mx, my);
        step = 4;
        return;
    }
    
    if (mapValue[bx/16][by/16] == 0 && mapValue[bx/16+1][by/16] == 0 &&
        mapValue[bx/16][by/16+1] == 0 && mapValue[bx/16+1][by/16+1] == 0)
    {
        shot += 1;
        power = 0;
        step = 1;
        return;
    }
    
    if (fabsf(mx) < 0.5f && fabsf(my) < 0.5f && std::abs(c) < 3 && std::abs(d) < 3) {
        power = 0;
        step = 1;
        return;
    }
}

void Update()
{
    if (Input::GetKeyDown(KeyMask::Q)) {
        hole--;
        if (hole < 0) {
            hole = 17;
        }
        LoadHoleData();
    }
    if (Input::GetKeyDown(KeyMask::W)) {
        hole++;
        if (hole > 17) {
            hole = 0;
        }
        LoadHoleData();
    }
    if (step == 1) {
        if (Input::GetKey(KeyMask::LeftArrow)) {
            angle -= Time::deltaTime * M_PI;
        }
        if (Input::GetKey(KeyMask::RightArrow)) {
            angle += Time::deltaTime * M_PI;
        }
        if (Input::GetKeyDown(KeyMask::Space)) {
            step++;
        }
    } else if (step == 2) {
        power += Time::deltaTime * powerSpeed;
        if (power <= 0.0f) {
            power = 0.0f;
            powerSpeed *= -1;
        }
        if (power >= 1.0f) {
            power = 1.0f;
            powerSpeed *= -1;
        }
        if (Input::GetKeyDown(KeyMask::Space)) {
            mx = cosf(angle) * (power * 8 + 1);
            my = sinf(angle) * (power * 8 + 1);
            step++;
        }
    } else if (step == 3) {
        ProcessShot();
    }
    
    Clear(Color::darkblue);
    
    SetCameraTranslation(Screen::size()/2);
    DrawMap();
    DrawInfoTexts();
    DrawBall();
    
    if (step == 1 || step == 2) {
        DrawTarget();
    }
    if (step == 2 || step == 3) {
        DrawPower();
    }
}

