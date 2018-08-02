#include "CRectangle.h"

CRectangle::CRectangle(const CVector2&position, const CVector2&scale, CTexture*texture)
:mPosition(position), mScale(scale)
{
	mPosition.x = position.x;
	mPosition.y = position.y;
};

void CRectangle::SetVertex(float Left, float Right, float Bottom, float Top){
	/*四角形を
	左上、左下、右下、右上の頂点順で作る
	*/
	mVector[0].x = Left;	mVector[0].y = Top;
	mVector[1].x = Left;	mVector[1].y = Bottom;
	mVector[2].x = Right;	mVector[2].y = Bottom;
	mVector[3].x = Right;	mVector[3].y = Top;

	mLeft = Left;
	mRight = Right;
	mBottom = Bottom;
	mTop = Top;
}
void CRectangle::Update(){
	//移動行列
	mMatrix.SetTranslate(mPosition.x, mPosition.y);
	//マトリクスクラスを回転、拡宿用行列
	CMatrix33 rot, sca;
	//回転行列
	rot.SetRotation(mRotation);
	//拡大縮小行列
	sca.SetScale(mScale.x, mScale.y);
}

void CRectangle::Render(float r, float g, float b, float a){
	glColor4f(r, g, b, a);
	CVector2 mv[4];	//座標で四角形生成するためのインスタンス
	//合成行列を代入する
	mv[0] = mMatrix.MultiVector2(mVector[0]);
	mv[1] = mMatrix.MultiVector2(mVector[1]);
	mv[2] = mMatrix.MultiVector2(mVector[2]);
	mv[3] = mMatrix.MultiVector2(mVector[3]);
	if (!mEnabled)	//有効フラグが無効な時は戻り値を返す
		return;
	else{	//フラグが有効な時は四角形を生成する
		glBegin(GL_QUADS);
		glVertex2f(mv[0].x, mv[0].y);
		glVertex2f(mv[1].x, mv[1].y);
		glVertex2f(mv[2].x, mv[2].y);
		glVertex2f(mv[3].x, mv[3].y);
		glEnd();
	}
}