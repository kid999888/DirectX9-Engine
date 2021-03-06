//=============================================================================
//!	@file	Types.h
//!	@brief	型の定義、インクルードの設定、そして、便利ツール
//!	@date	2018.10.31
//!	@note	型サポートプログラム
//!	@author	王暁晨(AT-13A-281 04)
//=============================================================================

#pragma once
//=============================================================================
//　　　ヘッダファイル
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <assert.h>

#include <algorithm>
#include <vector>
#include <map>
#include <set>

#pragma comment (lib, "Winmm.lib")
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3dx9d.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3dcompiler.lib")


//=============================================================================
//　　　便利ツール
//=============================================================================
#define SAFE_DELETE(ptr)		{ if (ptr != NULL) { delete ptr; } }					//! @brief安全消しマクロ
#define SAFE_DELETE_ARRAY(ptr)	{ if (ptr != NULL) { delete[] ptr; ptr = NULL;} }		//! @brief安全配列消しマクロ	
#define SAFE_RELEASE(ptr)		{ if (ptr != NULL) { ptr->Release(); ptr = NULL; } }	//! @brief安全リリースマクロ
#define SAFE_ADDREF(ptr)		{ if (ptr != NULL) { ptr->AddRef(); } }					//! @brief安全参照カウンタゼロ化

#if defined(_DEBUG)
#define HALT()				{ *reinterpret_cast<int*>(0x0) = 0; }						//! @brief初期化
#define ASSERT(expression)	{ if (!(expression)) HALT(); }								//! @briefポインタの検査する
#else//defined(_DEBUG)
#define HALT()																			//! @brief初期化
#define ASSERT(a)																		//! @briefポインタの検査する（無効にする）
#endif//defined(_DEBUG)

//==============================================================================
//　　　比較ツール
//==============================================================================
//==============================================================================
//!	@fn		Clamp
//!	@brief	数値範囲内が判断の処理
//!	@param	T任意 value 比較の値
//!	@param	T任意 min 最小値
//!	@param	T任意 max 最大値
//!	@retval	T任意 処理後の値
//==============================================================================
//inline float Clamp(float value, float min, float max)
//{
//	return value < min
//		? min
//		: value > max
//		? max
//		: value;
//}
template <typename T>
T Clamp(T value, T min, T max)
{
	assert("Clamp()不正な最大最小値順番" && min <= max);
	return (std::min)((std::max)(value, min), max);
}

//==============================================================================
//!	@fn		Clamp01
//!	@brief	数値範囲内（0.0f〜1.0f）が判断の処理
//!	@param	T任意 value 
//!	@retval	T任意 処理後の値
//==============================================================================
//inline float Clamp01(float value)
//{
//	return Clamp(value, 0.0f, 1.0f);
//}
template <typename T>
T Clamp01(T value)
{
	return Clamp(value, 0.0f, 1.0f);
}

//==============================================================================
//!	@fn		Saturate
//!	@brief	Clamp01(value)も一度実行します
//!	@param	T任意 value 
//!	@retval	T任意 処理後の値
//==============================================================================
//inline float Saturate(float value)
//{
//	return Clamp01(value);
//}
template <typename T>
T Saturate(T value)
{
	return Clamp01(value);
}

//==============================================================================
//!	@fn		Lerp
//!	@brief	数値線形補間するプログラム
//!	@param	T任意 a 最初の値
//!	@param	T任意 b 最後の値
//!	@param	T任意 r 補間の比率
//!	@retval	T任意 処理後の値
//==============================================================================
inline float Lerp(float a, float b, float r)
{
	return a + (b - a) * r;
}
//template <typename T>
//inline T const& Lerp(float const& a, float const& b, float const& r)
//{
//	return a + (b - a) * r;
//}

//==============================================================================
//　　　自作ポイント型（int）
//==============================================================================
//==============================================================================
//!	@struct	Point2DI
//!	@brief	2Dポイント情報情報(int)
//==============================================================================
//struct Point2DI
//{
//	int x, y;
//};
//==============================================================================
//!	@struct	Point3DI
//!	@brief	3Dポイント情報情報(int)
//==============================================================================
//struct Point3DI
//{
//	int x, y, z;
//};
//==============================================================================
//!	@struct	Point4DI
//!	@brief	4Dポイント情報情報(int)
//==============================================================================
//struct Point4DI
//{
//	int x, y, z, w;
//};

//==============================================================================
//　　　自作ポイント型（float）
//==============================================================================
//==============================================================================
//!	@struct	Point2DF
//!	@brief	2Dポイント情報情報(float)
//==============================================================================
//struct Point2DF
//{
//	float x, y;
//};
//==============================================================================
//!	@struct	Point3DF
//!	@brief	3Dポイント情報情報(float)
//==============================================================================
//struct Point3DF
//{
//	float x, y, z;
//};
//==============================================================================
//!	@struct	Point4DF
//!	@brief	4Dポイント情報情報(float)
//==============================================================================
//struct Point4DF
//{
//	float x, y, z, w;
//};

//==============================================================================
//!	@fn		FileData
//!	@brief	ファイルを読み込む時のメモ帳
//==============================================================================
typedef std::vector<char>	FileData;

//==============================================================================
//!	@struct	FileLoader
//!	@brief	ファイルを読み込むの構造体
//==============================================================================
//struct FileLoader
//{
//	//==============================================================================
//	//!	@fn		Load
//	//!	@brief	ファイルを読み込む処理
//	//!	@param	const char* pFileName ファイルパス
//	//!	@param	FileData& Binary 読み込んでいるのメモ帳
//	//!	@retval	FileDat std::Vector<char> 読み込んだのVector<char>
//	//==============================================================================
//	static FileData& Load(const char* pFileName, FileData& Binary)
//	{
//		Binary.clear();
//		FILE* fp = fopen(pFileName, "rb");
//		if (fp != NULL)
//		{
//			fseek(fp, 0, SEEK_END);
//			Binary.resize(ftell(fp));
//			if (Binary.size() > 0)
//			{
//				fseek(fp, 0, SEEK_SET);
//				fread(&(Binary[0]), Binary.size(), 1, fp);
//			}
//			fclose(fp);
//		}
//		return Binary;
//	}
//};