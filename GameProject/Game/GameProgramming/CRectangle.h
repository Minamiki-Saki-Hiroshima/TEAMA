#ifndef CRECTANGLE_H
#define CRECTANGLE_H
#include "CTask.h"
#include "CVector2.h"
#include "CTexture.h"
#include "CMatrix33.h"

class CRectangle : public CTask{
public:
	CVector2 mPosition;	//四角形の中心座標	x四角形の中心のX座標	y四角形の中心Y座標
	CVector2 mVector[4];	//四角形生成メソッドに使うインスタンス変数
	CVector2 mScale;	//四角形の幅と高さ
	CTexture*mpTexture;	//四角形が使用するテクスチャへのポインタ
	CMatrix33 mMatrix;	//マトリクスをインスタンスにする(これは移動行列用)
	float mRotation;	//四角形の回転角度
	float mUv[4];	//テクスチャマッピングデータ
	/*
	position:位置
	scale:大きさ
	texture:テクスチャの有無(有:テクスチャのインスタンス,無:0)
	*/
	CRectangle(const CVector2&position, const CVector2&scale, CTexture*texture);
	void SetVertex(float mLeft, float mRight, float mBottom, float mTop);	//四角形生成メソッド
	void Update();	//更新処理
	void Render();	//描画処理

};
#endif