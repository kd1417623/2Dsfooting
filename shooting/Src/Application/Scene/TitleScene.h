#pragma once
#include "SceneBase.h"
class TitleScene :public SceneBase
{
public:
	TitleScene ();
	~TitleScene ();

	void Update() override;
	void Init() override;
	void Draw() override;
	void PreUpdate() override;

private:

};

