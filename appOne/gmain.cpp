#if 1
#include"libOne.h"

struct DATA {
    int INIT = 0;
    int PLAY = 1;
    int RESULT = 2;
    int state = INIT;
};

void loadImages(struct DATA* d) {}
void init(struct DATA* d) {}
void play(struct DATA* d) {}
void result(struct DATA* d) {}
void draw(struct DATA* d) {}

void gmain() {
    window(800, 450);
    struct DATA d;
    loadImages(&d);
    while (notQuit) {
        if      (d.state == d.INIT  ) { init(&d); }
        else if (d.state == d.PLAY  ) { play(&d); }
        else if (d.state == d.RESULT) { result(&d); }
        draw(&d);
    }
}

#else

#include"libOne.h"
void draw(struct DATA* d);
void drawResult(struct DATA* d);

struct DATA {
    //��̔ԍ������߂Ă���
    int GU = 0;
    int CHOKI = 1;
    int PA = 2;
    //�v���C���[�f�[�^
    int playerHand;
    int playerGuImg;
    int playerChokiImg;
    int playerPaImg;
    int playerImg;
    float playerPx;
    float playerPy;
    float playerAngle;
    float playerR;
    float playerG;
    float playerB;
    int playerLife;
    //�o�b�f�[�^
    int pcHand;
    int pcGuImg;
    int pcChokiImg;
    int pcPaImg;
    int pcImg;
    float pcPx;
    float pcPy;
    float pcAngle;
    float pcR;
    float pcG;
    float pcB;
    int pcLife;
    //�n�[�g�摜�ԍ�
    int heartImg;
    //�������������p
    float resultPx;
    float resultPy;
    float resultSize;
    //��Ԑ؂�ւ�
    int INIT = 0;
    int PLAY = 1;
    int RESULT = 2;
    int state = INIT;
};

void loadImages(struct DATA* d) {
    //�摜�ǂݍ���-----------------------------------------------------
    d->playerGuImg = loadImage("assets\\playerGu.png");
    d->playerChokiImg = loadImage("assets\\playerChoki.png");
    d->playerPaImg = loadImage("assets\\playerPa.png");
    d->pcGuImg = loadImage("assets\\pcGu.png");
    d->pcChokiImg = loadImage("assets\\pcChoki.png");
    d->pcPaImg = loadImage("assets\\pcPa.png");
    d->heartImg = loadImage("assets\\heart.png");
}
void init(struct DATA* d) {
    //�������O�����l�ݒ�
    //�v���C���[�f�[�^
    d->playerHand = d->GU;
    d->playerImg = d->playerGuImg;
    d->playerPx = 250;
    d->playerPy = 225;
    d->playerAngle = 0;
    d->playerR = 255;
    d->playerG = 255;
    d->playerB = 255;
    d->playerLife = 3;
    //�o�b�f�[�^
    d->pcHand = d->GU;
    d->pcImg = d->pcGuImg;
    d->pcPx = 550;
    d->pcPy = 225;
    d->pcAngle = 0;
    d->pcR = 255;
    d->pcG = 255;
    d->pcB = 255;
    d->pcLife = 3;
    //������������
    d->resultPx = 225;
    d->resultPy = 320;
    d->resultSize = 0;
    //�Q�[���X�e�[�g�؂�ւ�
    d->state = d->PLAY;
}
void play(struct DATA* d) {
    //A,S,D�̃L�[�͂ǂ��������Ă��Ȃ�
    if (!isTrigger(KEY_A) && !isTrigger(KEY_S) && !isTrigger(KEY_D)) {
        draw(d);
        return;
    }
    //�v���C���[�̎�����߂�---------------------------------------
    if      (isTrigger(KEY_A)) { d->playerHand = d->GU; }
    else if (isTrigger(KEY_S)) { d->playerHand = d->CHOKI; }
    else if (isTrigger(KEY_D)) { d->playerHand = d->PA; }
    //�v���C���[�̉摜��؂�ւ���
    if      (d->playerHand == d->GU   ) { d->playerImg = d->playerGuImg; }
    else if (d->playerHand == d->CHOKI) { d->playerImg = d->playerChokiImg; }
    else if (d->playerHand == d->PA   ) { d->playerImg = d->playerPaImg; }
    //�o�b�̎�����߂�---------------------------------------------
    d->pcHand = random() % 3;
    //�o�b�̉摜��؂�ւ���
    if (d->pcHand == d->GU) { d->pcImg = d->pcGuImg; }
    else if (d->pcHand == d->CHOKI) { d->pcImg = d->pcChokiImg; }
    else if (d->pcHand == d->PA) { d->pcImg = d->pcPaImg; }
    //�����������肵�A�F��ς���-----------------------------------
    if (d->playerHand == d->pcHand) {
        //������
        d->playerR = 255; d->playerG = 255; d->playerB = 255;
        d->pcR = 255; d->pcG = 255; d->pcB = 255;
    }
    else if ((d->playerHand + 1) % 3 == d->pcHand) {
        //�v���C���[����
        d->playerR = 255; d->playerG = 200; d->playerB = 200;
        d->pcR = 255; d->pcG = 255; d->pcB = 255;
        d->pcLife--;
    }
    else {
        //�o�b����
        d->playerR = 255; d->playerG = 255; d->playerB = 255;
        d->pcR = 255; d->pcG = 200; d->pcB = 200;
        d->playerLife--;
    }
    //�`��---------------------------------------------------------
    draw(d);
    //�Q�[���X�e�[�g�؂�ւ�---------------------------------------
    if (d->playerLife == 0 || d->pcLife == 0) {
        d->state = d->RESULT;
    }
}
void result(struct DATA* d) {
    if (d->pcLife == 0) {
        //�o�b����
        d->pcPy += 1.0f;
        d->pcAngle += -0.005f;
    }
    else {
        //�v���C���[����
        d->playerPy += 1.0f;
        d->playerAngle += 0.005f;
    }
    //��������������傫�����Ă���
    if (d->resultSize < 180) {
        d->resultSize += 10.0f;
    }
    //�`��
    draw(d);
    drawResult(d);

    //�Q�[���X�e�[�g�؂�ւ�
    if (isTrigger(KEY_SPACE)) {
        d->state = d->INIT;
    }
}
void draw(struct DATA* d) {
    clear(200);
    //�v���C���[�̎�
    rectMode(CENTER);
    imageColor(d->playerR, d->playerG, d->playerB);
    image(d->playerImg, d->playerPx, d->playerPy, d->playerAngle);
    //�o�b�̎�
    imageColor(d->pcR, d->pcG, d->pcB);
    image(d->pcImg, d->pcPx, d->pcPy, d->pcAngle);
    //�v���C���[�n�[�g
    imageColor(255, 0, 0);
    for (int i = 0; i < d->playerLife; i++) {
        image(d->heartImg, d->playerPx - 50 + i * 50, d->playerPy - 110);
    }
    //�o�b�n�[�g
    for (int i = 0; i < d->pcLife; i++) {
        image(d->heartImg, d->pcPx - 50 + i * 50, d->pcPy - 110);
    }
}
void drawResult(struct DATA* d) {
    textSize(d->resultSize);
    if (d->playerLife > 0) {
        fill(255, 0, 0);
        text("����", d->resultPx, d->resultPy);
    }
    else {
        fill(0, 0, 200);
        text("����", d->resultPx, d->resultPy);
    }
}

void gmain(){
    //�E�B���h�E�\��
    window(800, 450);
    //�f�[�^�p��
    struct DATA d;
    //�摜�ǂݍ���
    loadImages(&d);
    //���C�����[�v
    while (notQuit) {
        //�X�e�[�g����
        if      (d.state == d.INIT  ) { init(&d); }
        else if (d.state == d.PLAY  ) { play(&d); }
        else if (d.state == d.RESULT) { result(&d); }
    }
}

#endif

