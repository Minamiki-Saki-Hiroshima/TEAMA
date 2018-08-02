#include <stdio.h>	//ファイルの入力に使用
#include "CTexture.h"

void CTexture::Load(const char* filename) {
	//画像データ
	unsigned char* data;
	//ファイルポインタの作成
	FILE *fp;
	errno_t error;
	//ファイルオープン
	error = fopen_s(&fp, filename, "rb");
	//エラーのときはリターン
	if (error != 0) {
		printf("file not found:%s\n", filename);
		return;
	}
	//ヘッダ情報を読み込む
	fread(&header, sizeof(header), 1, fp);
	//画像データのバイト数を計算する
	int length = header.width * header.height * header.depth / 8;
	//画像データの格納領域を確保
	data = new unsigned char[length];
	//画像データをヘッダの続きから読み込む
	fread(data, length, 1, fp);
	//画像ファイルのクローズ
	fclose(fp);

	//テクスチャデータの作成
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//バイリニア法
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//バイリニア法
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	//ニアレストネイバー法
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	//ニアレストネイバー法
	if (header.depth == 32)
		//アルファ有りのテクスチャ作成
		gluBuild2DMipmaps(GL_TEXTURE_2D, 4, header.width,
		header.height, GL_BGRA_EXT, GL_UNSIGNED_BYTE, data);
	else
		//アルファ無しのテクスチャ作成
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, header.width,
		header.height, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
	//格納領域を解放
	delete[] data;
}

/*
DrawImage
left:四角形左座標
right:四角形右座標
bottom:四角形下座標
top:四角形上座標
tleft:画像左座標
tright:画像右座標
tbottom:画像下座標
ttop:画像上座標
r:赤 色の加算
g:緑 色の加算
b:青 色の加算
alpha:画像の透明度
*/

void CTexture::SetDrawImage(int left, int right, int bottom, int top, float tleft, float tright, float tbottom, float ttop, float r, float g, float b, float alpha){
	//テクスチャを有効にする
	glEnable(GL_TEXTURE_2D);
	//アルファブレンドを有効にする
	glEnable(GL_BLEND);
	//ブレンド方法を指定
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//通常 アルファブレンド
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE);	//加算 アルファブレンド

	//テクスチャを指定
	glBindTexture(GL_TEXTURE_2D, id);

	glColor4f(r, g, b, alpha);

	glBegin(GL_TRIANGLES);
	glTexCoord2f(tleft / header.width, (header.height - ttop) / header.height);
	glVertex2d(left, top);
	glTexCoord2f(tleft / header.width, (header.height - tbottom) / header.height);
	glVertex2d(left, bottom);
	glTexCoord2f(tright / header.width, (header.height - tbottom) / header.height);
	glVertex2d(right, bottom);
	glTexCoord2f(tleft / header.width, (header.height - ttop) / header.height);
	glVertex2d(left, top);
	glTexCoord2f(tright / header.width, (header.height - tbottom) / header.height);
	glVertex2d(right, bottom);
	glTexCoord2f(tright / header.width, (header.height - ttop) / header.height);
	glVertex2d(right, top);
	glEnd();

	//テクスチャを解放
	glBindTexture(GL_TEXTURE_2D, 0);
	//アルファブレンドを無効
	glDisable(GL_BLEND);
	//テクスチャを無効
	glDisable(GL_TEXTURE_2D);
}

void CTexture::DrawImage(int left, int right, int bottom, int top, float tleft, float tright, float tbottom, float ttop, float alpha){
	SetDrawImage(left, right, bottom, top, tleft, tright, tbottom, ttop, 1.0f, 1.0f, 1.0f, alpha);
}

void CTexture::DrawImageSetColor(int left, int right, int bottom, int top, float tleft, float tright, float tbottom, float ttop, float r, float g, float b, float alpha){
	SetDrawImage(left, right, bottom, top, tleft, tright, tbottom, ttop, r, g, b, alpha);
}