#if defined(__linux__)
#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/Random.h"
#include "/home/codeleaded/System/Static/Library/TransformedView.h"
#include "/home/codeleaded/System/Static/Library/MFunc_Parser.h"
#elif defined(_WINE)
#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/Random.h"
#include "/home/codeleaded/System/Static/Library/TransformedView.h"
#include "/home/codeleaded/System/Static/Library/MFunc_Parser.h"
#elif defined(_WIN32)
#include "F:/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "F:/home/codeleaded/System/Static/Library/Random.h"
#include "F:/home/codeleaded/System/Static/Library/TransformedView.h"
#include "F:/home/codeleaded/System/Static/Library/MFunc_Parser.h"
#elif defined(__APPLE__)
    #error "Apple not supported!"
#else
    #error "Platform not supported!"
#endif

void Function_Render(unsigned int* Target,int Width,int Height,unsigned int color,TransformedView* tv,MFunc_Parser* mfp,Token* t){
	MFunc_Var* x_var = MFunc_Parser_FindVar(mfp,"x");
	if(!x_var) return;

	Vec2 PosBefore = { 0.0f,0.0f };
	for(int i = 0;i<GetWidth();i++){
		Vec2 Pos = { i,0.0f };
		
		float x = TransformedView_ScreenWorldX(tv,i);

		x_var->v = (MFunc_Real)x;
		Pos.y = TransformedView_WorldScreenY(tv,-MFunc_Parser_ExeReal(mfp,t));
		
		//Token ret = MFunc_Parser_Exe(mfp,t);
		//Pos.y = TransformedView_WorldScreenY(tv,-F64_Parse(ret.str));
		//Token_Free(&ret);
		
		if(!((Pos.y < 0.0f && PosBefore.y < 0.0f) ||
			 (Pos.y >= GetHeight() && PosBefore.y >= GetHeight())))
			RenderLine(PosBefore,Pos,color,1.0f);

		PosBefore = Pos;
	}
}


MFunc_Parser mfp;
TextBox tb;
TransformedView tv;

void Setup(AlxWindow* w){
	tv = TransformedView_Make(
		(Vec2){ GetWidth(),GetHeight() },
		(Vec2){ -25.0f,-50.0f },
		(Vec2){ 0.01f,0.01f },
		(float)GetWidth() / (float)GetHeight()
	);

	tb = TextBox_New(Input_New(50,1),(Rect){0.0f,0.0f,2300.0f,100.0f},ALXFONT_PATHS_HIGH,50,100,BLACK);
	
	mfp = MFunc_Parser_New();
    MFunc_Parser_Var(&mfp,MFunc_Var_New(0.0,"x",0));
    //MFunc_Parser_Add(&mfp,"0.0");
}
void Update(AlxWindow* w){
	TransformedView_HandlePanZoom(&tv,window.Strokes,GetMouse());
	
	if(Stroke(ALX_MOUSE_L).PRESSED) {
		Vec2 m = TransformedView_ScreenWorldPos(&tv,GetMouse());
		printf("%f %f\n",m.x,m.y);
	}
	if(Stroke(ALX_KEY_ENTER).PRESSED) {
		if(tb.In.Buffer.size>0){
			CStr str = String_CStr(&tb.In.Buffer);
			if(str){
				MFunc_Parser_Add(&mfp,str);
				
				MFunc_Parser_Add(&mfp,str);
				MFunc_Parser_Do(&mfp,mfp.sts.size - 1,MFunc_Parser_Derivative);
				MFunc_Parser_Do(&mfp,mfp.sts.size - 1,MFunc_Parser_Compress);
    			
    			MFunc_Parser_Print(&mfp);
			}
			CStr_Free(&str);
		}
		tb.In.Enabled = 0;
	}else{
		TextBox_Update(&tb,w->Strokes,GetMouse());
	}

    Clear(BLACK);

	Vec2 wvls = { 0.0f,TransformedView_ScreenWorldY(&tv,0.0f) };
	Vec2 wvle = { 0.0f,TransformedView_ScreenWorldY(&tv,GetHeight()) };
	Vec2 whls = { TransformedView_ScreenWorldX(&tv,0.0f),0.0f };
	Vec2 whle = { TransformedView_ScreenWorldX(&tv,GetWidth()),0.0f };

	Vec2 svls = TransformedView_WorldScreenPos(&tv,wvls);
	Vec2 svle = TransformedView_WorldScreenPos(&tv,wvle);
	Vec2 shls = TransformedView_WorldScreenPos(&tv,whls);
	Vec2 shle = TransformedView_WorldScreenPos(&tv,whle);

	RenderLine(svls,svle,WHITE,1.0f);
	RenderLine(shls,shle,WHITE,1.0f);

	for(int i = 0;i<mfp.sts.size;i++){
		Token* t = (Token*)Vector_Get(&mfp.sts,i);
		const Pixel table[] = {
			RED,GREEN,BLUE,YELLOW,
			LIGHT_RED,LIGHT_GREEN,LIGHT_BLUE,LIGHT_YELLOW,
			DARK_RED,DARK_GREEN,DARK_BLUE,DARK_YELLOW
		};
		const Pixel p = table[i % (sizeof(table) / sizeof(*table))];
		Function_Render(WINDOW_STD_ARGS,p,&tv,&mfp,t);
	}

	RenderTextBox(&tb);
}
void Delete(AlxWindow* w){
    MFunc_Parser_Free(&mfp);
	TextBox_Free(&tb);
}

int main(){
    if(Create("Geogebra 2.3",2500,1200,1,1,Setup,Update,Delete))
        Start();
    return 0;
}