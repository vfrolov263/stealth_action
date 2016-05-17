#include "Level.h"
#include "Game.h"
#include "Player.h"
#include "GameKeys.h"
#include <gl/gl.h>
#pragma comment(lib, "opengl32.lib")
#include "GameSettings.h"

CLevel::CLevel(CGame *pGame): _pGame(pGame)
{
	_pPlayer = new CPlayer(this);
	Load(1);
}

CLevel::~CLevel()
{
	delete _pPlayer;
}

void CALLBACK CLevel::Update(float fTime)
{
	/*
	«десь будет обновление противников и ловушек.
	*/

	_pPlayer->Update(fTime);
	
	for (vector<CEnemy *>::iterator it = _enemiesVect.begin(); it != _enemiesVect.end(); ++it)
		(*it)->Update(fTime);

	//multiset<Vector2f>::iterator it = _objects.insert(_pPlayer->GetPosition());

	for (vector<CEnemy *>::iterator it = _enemiesVect.begin(); it != _enemiesVect.end(); ++it)
	{
		if ((*it)->IsInVisibilityZone(_pPlayer->GetPosition()))
			_pGame->SetState(GS_RESTART);

		(*it)->UpdateVisibilityZone(_objects);
	}

	if (_pPlayer->GetPosition() == pFinishSpr->GetBasis().position)
		_pGame->SetState(GS_MENU);

	//_objects.erase(it);
}

void CALLBACK CLevel::Draw()
{
	/*
	«десь будет прорисовка противников и ловушек.
	*/

	glBegin(GL_LINES);
	for (int i = 0; i < 800; i += 32)
	{
		glVertex2i(i, 0);
		glVertex2i(i, 600);
	}

	for (int i = 0; i < 600; i += 32)
	{
		glVertex2i(0, i);
		glVertex2i(800, i);
	}
	glEnd();

	for (vector<ISprite *>::iterator it = _tilesZeroVect.begin(); it != _tilesZeroVect.end(); ++it)
		(*it)->Draw();

	for (vector<ISprite *>::iterator it = _tilesOneVect.begin(); it != _tilesOneVect.end(); ++it)
		(*it)->Draw();

	pFinishSpr->Draw();

	_pPlayer->Draw();
	
	for (vector<CEnemy *>::iterator it = _enemiesVect.begin(); it != _enemiesVect.end(); ++it)
		(*it)->Draw();

	if (pInput->IsKeyDown(GK_SHOW_VISIBILITY))
		for (vector<CEnemy *>::iterator it = _enemiesVect.begin(); it != _enemiesVect.end(); ++it)
			(*it)->DrawVisibility();

	for (vector<ISprite *>::iterator it = _tilesTwoVect.begin(); it != _tilesTwoVect.end(); ++it)
		(*it)->Draw();

	/*glBegin(GL_QUADS);
	for (int i = 0; i < _levSize.x; ++i)
		for (int j = 0; j < _levSize.y; ++j)
		{
			if (_collMap[i][j])
			{
				glVertex2f(i * 32, j * 32 + 32);
				glVertex2f(i * 32, j* 32 );
				glVertex2f(i * 32 + 32, j * 32);
				glVertex2f(i * 32 + 32, j * 32 + 32);
			}
		}
	glEnd();*/
}

void CALLBACK CLevel::GetLevelParam(string &stringLevLine, cstr cstrParamName, str strParam)
{
	string stringParamName(cstrParamName);
	stringParamName += '=';
	int iPos = stringLevLine.find(stringParamName.c_str());
	int iPosExt = stringLevLine.find('"', iPos);
	int iPosExtEnd = stringLevLine.find('"', iPosExt + 1);
	string stringSubstr = stringLevLine.substr(iPosExt + 1, iPosExtEnd - iPosExt - 1);
	strcpy(strParam, stringSubstr.c_str());
}

void CALLBACK CLevel::AddTile(int iLayerNum, uint uiFrameNum, Vector2f &position)
{
	IAnimation *pAnim;
	ISprite *pSprite;
	uint uiFramesNum;

	for (vector<IAnimation *>::iterator it = _animsVect.begin(); it != _animsVect.end(); ++it)
	{
		pAnim = (*it);
		uiFramesNum = pAnim->GetFramesNumber();

		if (uiFrameNum < uiFramesNum)
		{
			pAnim->SetCurrentFrame(uiFrameNum);
			pSprite = 0;
			pComponentsManager->GetComponent((IComponent *&)pSprite, GCT_SPRITE);
			pSprite->SetTexture(pAnim->GetTexture()->GetName());
			pSprite->SetFrame(pAnim->GetFrame());
			pSprite->SetPosition(position);
			
			switch (iLayerNum)
			{
			case 0:
				_tilesZeroVect.push_back(pSprite);
				break;
			case 1:
				_tilesOneVect.push_back(pSprite);
				break;
			case 2:
				_tilesTwoVect.push_back(pSprite);
				break;
			}
		}
	}
}

void CALLBACK CLevel::InitVisibility()
{
	for (int i = 0; i < _levSize.x; ++i)
		for (int j = 0; j < _levSize.y; ++j)
			if (_collMap[i][j])
				_objects.insert(Vector2f(i * TILE_SIZE, j * TILE_SIZE));
}

bool CALLBACK CLevel::Load(int iNumber)
{
	string stringLevName("level_");
	stringLevName += '0' + iNumber;
	stringLevName += ".tmx";
	ifstream levFile(stringLevName.c_str());

	if (!levFile.is_open())
		return false;

	char strLine[MAX_LINE] = {0};
	char strParam[MAX_PARAM_LENGTH] = {0};
	char strTextName[MAX_LINE] = {0};
	int iLayerNum = 0;
	string stringLine, stringObjType;
	int iPos = 0; int iZ = 0;
	Vector2f position;
	Vector2i levSize, frameSize, indentSize;
	uint uiFrameNum;
	IComponent *pComponent = 0;
	Box2i objBox;
	IAnimation *pAnimation;
	//vectoonr<TDrawData> drawDataList;

	while (!levFile.eof())
	{
		levFile.getline(strLine, MAX_LINE);
		stringLine = string(strLine);

		if (stringLine.find("map version", 0) != string::npos)
		{
			GetLevelParam(stringLine, "width", strParam);
			sscanf(strParam, "%d", &_levSize.x);

			GetLevelParam(stringLine, "height", strParam);
			sscanf(strParam, "%d", &_levSize.y);
		}
		else if (stringLine.find("image source", 0) != string::npos)
		{
			GetLevelParam(stringLine, "image source", strParam);
			pComponentsManager->GetComponent((IComponent *&)pAnimation, GCT_ANIMATION);
			pAnimation->SetTexture(strParam);
			pAnimation->SetFrameSize(TILE_SIZE);
			_animsVect.push_back(pAnimation);
		}
		else if (stringLine.find("<layer", 0) != string::npos)
		{
			if (iLayerNum > 2)
				continue;

			levFile.getline(strLine, MAX_LINE);

			for (int j = 0; j < _levSize.y; ++j)
			{
				levFile.getline(strLine, MAX_LINE);
				int i = 0;

				for (str ptr = strLine; sscanf(ptr, "%d%n", &uiFrameNum, &iPos) > 0; ptr += iPos + 1, i++)
				{
					if (!uiFrameNum || uiFrameNum > 128)
						continue;

					AddTile(iLayerNum, uiFrameNum - 1, Vector2f(i * TILE_SIZE, j * TILE_SIZE));
				}
			}

			iLayerNum++;
		}
		else if (stringLine.find("object id", 0) != string::npos)
		{
			GetLevelParam(stringLine, "type", strParam);
			char strX[5] = {0}, strY[5] = {0};

			GetLevelParam(stringLine, "x", strX);
			GetLevelParam(stringLine, "y", strY);

			int iX, iY;
			sscanf(strX, "%d", &iX);
			sscanf(strY, "%d", &iY);

			iX /= TILE_SIZE;
			iY /= TILE_SIZE;

			iX *= TILE_SIZE;
			iY *= TILE_SIZE;

			CEnemy *pEnenmy;

			switch (strParam[0])
			{
			case 'p':
				_pPlayer->SetPosition(Vector2f(iX, iY));
				break;
			case 'e':
				pEnenmy = new CEnemy(Vector2f(iX, iY));
				GetLevelParam(stringLine, "name", strParam);

				for (int i = 0; i < strlen(strParam); ++i)
					pEnenmy->AddToTrajectory(strParam[i]);

				_enemiesVect.push_back(pEnenmy);


				break;
			case 'f':
				pFinishSpr->SetPosition(Vector2f(iX, iY));
				_finish.x = iX / TILE_SIZE;
				_finish.y = iY / TILE_SIZE;
				break;
			default:
				break;
			}
		}
		else if (stringLine.find("<collisions", 0) != string::npos)
		{
			_collMap = new bool *[_levSize.x];

			for (int i = 0; i < _levSize.x; ++i)
				_collMap[i] = new bool[_levSize.y];

			for (int j = 0; j < _levSize.y; ++j)
			{
				levFile.getline(strLine, MAX_LINE);

				for (int i = 0; i < _levSize.x; i++)
					_collMap[i][j] = strLine[i] - '0';
			}
		}
	}

	levFile.close();
	InitVisibility();
	return true;
}

bool CALLBACK CLevel::IsFreeCell(const Vector2f &position)
{
	int iX = position.x / TILE_SIZE;
	int iY = position.y / TILE_SIZE;
	return !_collMap[iX][iY];
}