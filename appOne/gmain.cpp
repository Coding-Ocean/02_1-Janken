#if 1

#include"libOne.h"
struct DATA {
    int playerGuImg;   
    int playerChokiImg;
    int playerPaImg;   
    int pcGuImg;       
    int pcChokiImg;    
    int pcPaImg;
    int heartImg;

    const int GU = 0;
    const int CHOKI = 1;
    const int PA = 2;

    //プレイヤーデータカード
    int playerHand;
    int playerImg;
    int playerLife;
    float playerPx;
    float playerPy;
    float playerR;
    float playerG;
    float playerB;
    float playerAngle;
    //ＰＣデータカード
    int pcHand;
    int pcImg;
    int pcLife;
    float pcPx;
    float pcPy;
    float pcR;
    float pcG;
    float pcB;
    float pcAngle;
    //勝ち負け文字用カード
    float resultPx;
    float resultPy;
    float resultSize;
    //シーケンス遷移
    const int INIT = 0;
    const int PLAY = 1;
    const int RESULT = 2;
    int state = INIT;
};
void draw(struct DATA* d);
void drawResult(struct DATA* d);
void loadImages(struct DATA* d) {
    d->playerGuImg = loadImage("assets\\playerGu.png");
    d->playerChokiImg = loadImage("assets\\playerChoki.png");
    d->playerPaImg = loadImage("assets\\playerPa.png");
    d->pcGuImg = loadImage("assets\\pcGu.png");
    d->pcChokiImg = loadImage("assets\\pcChoki.png");
    d->pcPaImg = loadImage("assets\\pcPa.png");
    d->heartImg = loadImage("assets\\heart.png");
}
void init(struct DATA* d) {
    //プレイヤーデータ
    d->playerHand = d->GU;
    d->playerImg = d->playerGuImg;
    d->playerPx = 250;
    d->playerPy = 225;
    d->playerR = 255;
    d->playerG = 255;
    d->playerB = 255;
    d->playerLife = 3;
    d->playerAngle = 0;
    //ＰＣデータ
    d->pcHand = d->GU;
    d->pcImg = d->pcGuImg;
    d->pcPx = 550;
    d->pcPy = 225;
    d->pcR = 255;
    d->pcG = 255;
    d->pcB = 255;
    d->pcLife = 3;
    d->pcAngle = 0;
    //勝ち負け文字
    d->resultPx = 225;
    d->resultPy = 320;
    d->resultSize = 0;
    //ゲームステート切り替え
    d->state = d->PLAY;
}
void play(struct DATA* d) {
    if (isTrigger(KEY_A) || isTrigger(KEY_S) || isTrigger(KEY_D)) {

        if (isTrigger(KEY_A)) { d->playerHand = d->GU; }
        else if (isTrigger(KEY_S)) { d->playerHand = d->CHOKI; }
        else if (isTrigger(KEY_D)) { d->playerHand = d->PA; }
        if (d->playerHand == d->GU) { d->playerImg = d->playerGuImg; }
        else if (d->playerHand == d->CHOKI) { d->playerImg = d->playerChokiImg; }
        else if (d->playerHand == d->PA) { d->playerImg = d->playerPaImg; }

        d->pcHand = random() % 3;
        if (d->pcHand == d->GU) { d->pcImg = d->pcGuImg; }
        else if (d->pcHand == d->CHOKI) { d->pcImg = d->pcChokiImg; }
        else if (d->pcHand == d->PA) { d->pcImg = d->pcPaImg; }

        //勝ち負け判定し、色を変える
        if (d->playerHand == d->pcHand) {
            //あいこ
            d->playerR = 255; d->playerG = 255; d->playerB = 255;
            d->pcR = 255;     d->pcG = 255;     d->pcB = 255;
        }
        else if ((d->playerHand + 1) % 3 == d->pcHand) {
            //プレイヤー勝ち
            d->playerR = 255; d->playerG = 200; d->playerB = 200;
            d->pcR = 255;     d->pcG = 255;     d->pcB = 255;
            d->pcLife--;
        }
        else {
            //ＰＣ勝ち
            d->playerR = 255; d->playerG = 255; d->playerB = 255;
            d->pcR = 255;     d->pcG = 200;     d->pcB = 200;
            d->playerLife--;
        }
        //ゲームステート切り替え
        if (d->playerLife == 0 || d->pcLife == 0) {
            d->state = d->RESULT;
        }
    }
    draw(d);
}
void result(struct DATA* d) {
    //試合終了
    if (d->pcLife == 0) {
        //ＰＣ負け
        d->pcPy += 1.0f;
        d->pcAngle += -0.005f;
    }
    else {
        //プレイヤー負け
        d->playerPy += 1.0f;
        d->playerAngle += 0.005f;
    }
    //勝ち負け文字の大きさ
    if (d->resultSize < 180) {
        d->resultSize += 10.0f;
    }
    //ゲームステート切り替え
    if (isTrigger(KEY_SPACE)) {
        d->state = d->INIT;
    }
    draw(d);
    drawResult(d);
}
void draw(struct DATA* d) {
    clear(200, 200, 200);
    //プレイヤーの手
    rectMode(CENTER);
    imageColor(d->playerR, d->playerG, d->playerB);
    image(d->playerImg, d->playerPx, d->playerPy, d->playerAngle);
    //ＰＣの手
    imageColor(d->pcR, d->pcG, d->pcB);
    image(d->pcImg, d->pcPx, d->pcPy, d->pcAngle);
    //プレイヤーハート
    imageColor(255, 0, 0);
    for (int i = 0; i < d->playerLife; i++) {
        image(d->heartImg, d->playerPx - 50 + i * 50, d->playerPy - 110);
    }
    //ＰＣハート
    for (int i = 0; i < d->pcLife; i++) {
        image(d->heartImg, d->pcPx - 50 + i * 50, d->pcPy - 110);
    }
}
void drawResult(struct DATA* d) {
    //勝ち負けテキスト
    textSize(d->resultSize);
    if (d->playerLife > 0) {
        fill(255, 0, 0);
        text("勝ち", d->resultPx, d->resultPy);
    }
    else {
        fill(0, 0, 200);
        text("負け", d->resultPx, d->resultPy);
    }
}
void gmain() {
    window(800, 450);
    struct DATA d;
    loadImages(&d);
    while (notQuit) {
        if      (d.state == d.INIT) { init(&d); }
        else if (d.state == d.PLAY) { play(&d); }
        else if (d.state == d.RESULT) { result(&d); }
    }
}

#else

#include"libOne.h"
void gmain(){
    //ウィンドウ表示（この命令は画像読み込みより前に出さなければならない）
    window(800, 450);
    //画像読み込み
    int playerGuImg    = loadImage("assets\\playerGu.png");
    int playerChokiImg = loadImage("assets\\playerChoki.png");
    int playerPaImg    = loadImage("assets\\playerPa.png");
    int pcGuImg        = loadImage("assets\\pcGu.png");
    int pcChokiImg     = loadImage("assets\\pcChoki.png");
    int pcPaImg        = loadImage("assets\\pcPa.png");
    int heartImg       = loadImage("assets\\heart.png");
    //手の番号定数を決めておく
    const int GU    = 0;
    const int CHOKI = 1;
    const int PA    = 2;
    //プレイヤーデータカード
    int playerHand;
    int playerImg;
    int playerLife;
    float playerPx;
    float playerPy;
    float playerR;
    float playerG;
    float playerB;
    float playerAngle;
    //ＰＣデータカード
    int pcHand;
    int pcImg;
    int pcLife;
    float pcPx;
    float pcPy;
    float pcR;
    float pcG;
    float pcB;
    float pcAngle;
    //勝ち負け文字用カード
    float resultPx;
    float resultPy;
    float resultSize;
    //状態切り替えカード
    const int INIT   = 0;
    const int PLAY   = 1;
    const int RESULT = 2;
    int state = INIT;
    //メインループ
    while (notQuit) {
        //データ更新-----------------------------------------------------------
        if (state == INIT) {
            //試合直前初期値設定
            //プレイヤーデータ
            playerHand = GU;
            playerImg = playerGuImg;
            playerPx = 250;
            playerPy = 225;
            playerR = 255;
            playerG = 255;
            playerB = 255;
            playerLife = 3;
            playerAngle = 0;
            //ＰＣデータ
            pcHand = GU;
            pcImg = pcGuImg;
            pcPx = 550;
            pcPy = 225;
            pcR = 255;
            pcG = 255;
            pcB = 255;
            pcLife = 3;
            pcAngle = 0;
            //勝ち負け文字
            resultPx = 225;
            resultPy = 320;
            resultSize = 0;
            //ゲームステート切り替え
            state = PLAY;
        }
        else if( state == PLAY ){
            //試合中
            //A,S,Dいずれかのキーが押されたら
            if (isTrigger(KEY_A) || isTrigger(KEY_S) || isTrigger(KEY_D)) {
                //プレイヤーの手を決める
                if      (isTrigger(KEY_A)) { playerHand = GU; }
                else if (isTrigger(KEY_S)) { playerHand = CHOKI; }
                else if (isTrigger(KEY_D)) { playerHand = PA; }
                //プレイヤーの画像を切り替える
                if      (playerHand == GU   ) { playerImg = playerGuImg; }
                else if (playerHand == CHOKI) { playerImg = playerChokiImg; }
                else if (playerHand == PA   ) { playerImg = playerPaImg; }
                //ＰＣの手を決める
                pcHand = random() % 3;
                //ＰＣの画像を切り替える
                if      (pcHand == GU   ) { pcImg = pcGuImg; }
                else if (pcHand == CHOKI) { pcImg = pcChokiImg; }
                else if (pcHand == PA   ) { pcImg = pcPaImg; }
                //勝ち負け判定し、色を変える
                if (playerHand == pcHand) {
                    //あいこ
                    playerR = 255; playerG = 255; playerB = 255;
                    pcR = 255;     pcG = 255;     pcB = 255;
                }
                else if ((playerHand + 1) % 3 == pcHand) {
                    //プレイヤー勝ち
                    playerR = 255; playerG = 200; playerB = 200;
                    pcR = 255;     pcG = 255;     pcB = 255;
                    pcLife--;
                }
                else {
                    //ＰＣ勝ち
                    playerR = 255; playerG = 255; playerB = 255;
                    pcR = 255;     pcG = 200;     pcB = 200;
                    playerLife--;
                }
                //ゲームステート切り替え
                if (playerLife == 0 || pcLife == 0) {
                    state = RESULT;
                }
            }
        }
        else if(state == RESULT){
            //試合終了
            if (pcLife == 0) {
                //ＰＣ負け
                pcPy += 1.0f;
                pcAngle += -0.005f;
            }
            else {
                //プレイヤー負け
                playerPy += 1.0f;
                playerAngle += 0.005f;
            }
            //勝ち負け文字の大きさ
            if (resultSize < 180) {
                resultSize += 10.0f;
            }
            //ゲームステート切り替え
            if (isTrigger(KEY_SPACE)) {
                state = INIT;
            }
        }
        //描画-----------------------------------------------------------------
        clear(200);
        //プレイヤーの手
        rectMode(CENTER);
        imageColor(playerR, playerG, playerB);
        image(playerImg, playerPx, playerPy,playerAngle);
        //ＰＣの手
        imageColor(pcR, pcG, pcB);
        image(pcImg, pcPx, pcPy,pcAngle);
        //プレイヤーハート
        imageColor(255, 0, 0);
        for (int i = 0; i < playerLife; i++) {
            image(heartImg, playerPx - 50 + i * 50, playerPy - 110);
        }
        //ＰＣハート
        for (int i = 0; i < pcLife; i++) {
            image(heartImg, pcPx - 50 + i * 50, pcPy - 110);
        }
        //勝ち負けテキスト
        if (state == RESULT) {
            textSize(resultSize);
            if (playerLife > 0) {
                fill(255, 0, 0);
                text("勝ち", resultPx, resultPy);
            }
            else {
                fill(0, 0, 200);
                text("負け", resultPx, resultPy);
            }
        }
    }
}

#endif