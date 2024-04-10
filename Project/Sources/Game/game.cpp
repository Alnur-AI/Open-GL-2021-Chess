#include "Application/application.h"
#include "Application/application_data.h"
#include "Engine/Render/world_renderer.h"
#include "Engine/Render/sprite.h"
#include "Engine/transform2d.h"
#include "Engine/input.h"
#include "Engine/time.h"
#include "player.h"



static WorldRenderer worldRenderer;
MousePosition mousePos;

bool someFigureSelected = false; // true - figure is selected      false -  figure is not selected
int selectedFigureID;


Sprite backgroundS;
Transform2D backgroundT;

Sprite tableS;
Transform2D tableT;

Sprite mouseS;
Transform2D mouseT;

Sprite selectS;
Transform2D selectT;


Player player[2];
Team turn = Team::White;

struct Map {
	int tableMap[8][8];
	int figureID[8][8];
}tableMap;




static mat3 cameraProjection;
static Transform2D cameraTransform;

void setFigurePointer(Team team, int ID) {
	switch (ID)
	{
	case 1:
		player[int(team)].pointer = player[int(Team::White)].king;
		break;
	case 2:
		player[int(team)].pointer = player[int(Team::White)].queen;
		break;
	case 3:
		player[int(team)].pointer = player[int(Team::White)].bishop[0];
		break;
	case 4:
		player[int(team)].pointer = player[int(Team::White)].bishop[1];
		break;
	case 5:
		player[int(team)].pointer = player[int(Team::White)].rook[0];
		break;
	case 6:
		player[int(team)].pointer = player[int(Team::White)].rook[1];
		break;
	case 7:
		player[int(team)].pointer = player[int(Team::White)].knight[0];
		break;
	case 8:
		player[int(team)].pointer = player[int(Team::White)].knight[1];
		break;
	case 9:
		player[int(team)].pointer = player[int(Team::White)].pawn[0];
		break;
	case 10:
		player[int(team)].pointer = player[int(Team::White)].pawn[1];
		break;
	case 11:
		player[int(team)].pointer = player[int(Team::White)].pawn[2];
		break;
	case 12:
		player[int(team)].pointer = player[int(Team::White)].pawn[3];
		break;
	case 13:
		player[int(team)].pointer = player[int(Team::White)].pawn[4];
		break;
	case 14:
		player[int(team)].pointer = player[int(Team::White)].pawn[5];
		break;
	case 15:
		player[int(team)].pointer = player[int(Team::White)].pawn[6];
		break;
	case 16:
		player[int(team)].pointer = player[int(Team::White)].pawn[7];
		break;

	case 17:
		player[int(team)].pointer = player[int(Team::Black)].king;
		break;
	case 18:
		player[int(team)].pointer = player[int(Team::Black)].queen;
		break;
	case 19:
		player[int(team)].pointer = player[int(Team::Black)].bishop[0];
		break;
	case 20:
		player[int(team)].pointer = player[int(Team::Black)].bishop[1];
		break;
	case 21:
		player[int(team)].pointer = player[int(Team::Black)].rook[0];
		break;
	case 22:
		player[int(team)].pointer = player[int(Team::Black)].rook[1];
		break;
	case 23:
		player[int(team)].pointer = player[int(Team::Black)].knight[0];
		break;
	case 24:
		player[int(team)].pointer = player[int(Team::Black)].knight[1];
		break;
	case 25:
		player[int(team)].pointer = player[int(Team::Black)].pawn[0];
		break;
	case 26:
		player[int(team)].pointer = player[int(Team::Black)].pawn[1];
		break;
	case 27:
		player[int(team)].pointer = player[int(Team::Black)].pawn[2];
		break;
	case 28:
		player[int(team)].pointer = player[int(Team::Black)].pawn[3];
		break;
	case 29:
		player[int(team)].pointer = player[int(Team::Black)].pawn[4];
		break;
	case 30:
		player[int(team)].pointer = player[int(Team::Black)].pawn[5];
		break;
	case 31:
		player[int(team)].pointer = player[int(Team::Black)].pawn[6];
		break;
	case 32:
		player[int(team)].pointer = player[int(Team::Black)].pawn[7];
		break;
	}
}

void LeftPressed()
{
	std::cout << "LEFT MOUSE PRESSED" << std::endl;

	//unitMouse.position = worldRenderer.screen_to_world(mousePos.x, mousePos.y);
	Transform2D checkSelect = worldRenderer.screen_to_world(mousePos.x, mousePos.y);
	selectT.position = vec2(2 * (floor((checkSelect.position.x) / 2.)) + 1, 2 * (floor((checkSelect.position.y) / 2.)) + 1);

	int selectMapX = selectT.position.x / 2 + 4; //  1  это 0 3 это 1 5 это 2 7 это 3
	int selectMapY = selectT.position.y / 2 + 4;

	std::cout << selectMapX << " " << selectMapY << std::endl;

	/*check what figure is selected*/
	switch (tableMap.figureID[selectMapX][selectMapY])
	{
	case 0:
		/*Is Empty*/
		if (selectedFigureID != 0) {
			setFigurePointer(turn, selectedFigureID);
			player[int(turn)].pointer.x = 3;// selectT.position.x;
			player[int(turn)].pointer.y = 3;// selectT.position.x;

			tableMap.tableMap[3][3] = int(player[int(turn)].team);
			tableMap.figureID[3][3] = selectedFigureID;

			player[int(turn)].king.isSelected = false;
			someFigureSelected = false;
			selectedFigureID = 0;
			break;
		}
		break;
	case 1: 
		if (player[int(Team::White)].king.isSelected) {
			/*is Black*/
			if (selectedFigureID > 16) {

			}
			/*is White or itself*/
			if (selectedFigureID == player[int(Team::White)].king.ID) {
				player[int(Team::White)].king.isSelected = false;
				someFigureSelected = false;
				break;
			}
			break;
		}

		player[int(Team::White)].king.isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::White)].king.ID;
		break;
	case 2:
		if (player[int(Team::White)].queen.isSelected) {
			player[int(Team::White)].queen.isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::White)].queen.isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::White)].queen.ID;
		break;
	case 3:
		if (player[int(Team::White)].bishop[0].isSelected) {
			player[int(Team::White)].bishop[0].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::White)].bishop[0].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::White)].bishop[0].ID;
		break;
	case 4:
		if (player[int(Team::White)].bishop[1].isSelected) {
			player[int(Team::White)].bishop[1].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::White)].bishop[1].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::White)].bishop[1].ID;
		break;
	case 5:
		if (player[int(Team::White)].rook[0].isSelected) {
			player[int(Team::White)].rook[0].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::White)].rook[0].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::White)].rook[0].ID;
		break;
	case 6:
		if (player[int(Team::White)].rook[1].isSelected) {
			player[int(Team::White)].rook[1].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::White)].rook[1].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::White)].rook[1].ID;
		break;
	case 7:
		if (player[int(Team::White)].knight[0].isSelected) {
			player[int(Team::White)].knight[0].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::White)].knight[0].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::White)].knight[0].ID;
		break;
	case 8:
		if (player[int(Team::White)].knight[1].isSelected) {
			player[int(Team::White)].knight[1].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::White)].knight[1].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::White)].knight[1].ID;
		break;
	case 9:
		if (player[int(Team::White)].pawn[0].isSelected) {
			player[int(Team::White)].pawn[0].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::White)].pawn[0].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::White)].pawn[0].ID;
		break;
	case 10:
		if (player[int(Team::White)].pawn[1].isSelected) {
			player[int(Team::White)].pawn[1].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::White)].pawn[1].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::White)].pawn[1].ID;
		break;
	case 11:
		if (player[int(Team::White)].pawn[2].isSelected) {
			player[int(Team::White)].pawn[2].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::White)].pawn[2].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::White)].pawn[2].ID;
		break;
	case 12:
		if (player[int(Team::White)].pawn[3].isSelected) {
			player[int(Team::White)].pawn[3].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::White)].pawn[3].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::White)].pawn[3].ID;
		break;
	case 13:
		if (player[int(Team::White)].pawn[4].isSelected) {
			player[int(Team::White)].pawn[4].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::White)].pawn[4].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::White)].pawn[4].ID;
		break;
	case 14:
		if (player[int(Team::White)].pawn[5].isSelected) {
			player[int(Team::White)].pawn[5].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::White)].pawn[5].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::White)].pawn[5].ID;
		break;
	case 15:
		if (player[int(Team::White)].pawn[6].isSelected) {
			player[int(Team::White)].pawn[6].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::White)].pawn[6].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::White)].pawn[6].ID;
		break;
	case 16:
		if (player[int(Team::White)].pawn[7].isSelected) {
			player[int(Team::White)].pawn[7].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::White)].pawn[7].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::White)].pawn[7].ID;
		break;

	case 16+1:
		if (player[int(Team::Black)].king.isSelected) {
			player[int(Team::Black)].king.isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::Black)].king.isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::Black)].king.ID;
		break;
	case 16 + 2:
		if (player[int(Team::Black)].queen.isSelected) {
			player[int(Team::Black)].queen.isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::Black)].queen.isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::Black)].queen.ID;
		break;
	case 16 + 3:
		if (player[int(Team::Black)].bishop[0].isSelected) {
			player[int(Team::Black)].bishop[0].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::Black)].bishop[0].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::Black)].bishop[0].ID;
		break;
	case 16 + 4:
		if (player[int(Team::Black)].bishop[1].isSelected) {
			player[int(Team::Black)].bishop[1].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::Black)].bishop[1].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::Black)].bishop[1].ID;
		break;
	case 16 + 5:
		if (player[int(Team::Black)].rook[0].isSelected) {
			player[int(Team::Black)].rook[0].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::Black)].rook[0].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::Black)].rook[1].ID;
		break;
	case 16 + 6:
		if (player[int(Team::Black)].rook[1].isSelected) {
			player[int(Team::Black)].rook[1].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::Black)].rook[1].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::Black)].bishop[1].ID;
		break;
	case 16 + 7:
		if (player[int(Team::Black)].knight[0].isSelected) {
			player[int(Team::Black)].knight[0].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::Black)].knight[0].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::Black)].knight[0].ID;
		break;
	case 16 + 8:
		if (player[int(Team::Black)].knight[1].isSelected) {
			player[int(Team::Black)].knight[1].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::Black)].knight[1].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::Black)].knight[1].ID;
		break;
	case 16 + 9:
		if (player[int(Team::Black)].pawn[0].isSelected) {
			player[int(Team::Black)].pawn[0].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::Black)].pawn[0].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::Black)].pawn[0].ID;
		break;
	case 16 + 10:
		if (player[int(Team::Black)].pawn[1].isSelected) {
			player[int(Team::Black)].pawn[1].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::Black)].pawn[1].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::Black)].pawn[1].ID;
		break;
	case 16 + 11:
		if (player[int(Team::Black)].pawn[2].isSelected) {
			player[int(Team::Black)].pawn[2].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::Black)].pawn[2].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::Black)].pawn[2].ID;
		break;
	case 16 + 12:
		if (player[int(Team::Black)].pawn[3].isSelected) {
			player[int(Team::Black)].pawn[3].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::Black)].pawn[3].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::Black)].pawn[3].ID;
		break;
	case 16 + 13:
		if (player[int(Team::Black)].pawn[4].isSelected) {
			player[int(Team::Black)].pawn[4].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::Black)].pawn[4].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::Black)].pawn[4].ID;
		break;
	case 16 + 14:
		if (player[int(Team::Black)].pawn[5].isSelected) {
			player[int(Team::Black)].pawn[5].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::Black)].pawn[5].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::Black)].pawn[5].ID;
		break;
	case 16 + 15:
		if (player[int(Team::Black)].pawn[6].isSelected) {
			player[int(Team::Black)].pawn[6].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::Black)].pawn[6].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::Black)].pawn[6].ID;
		break;
	case 16 + 16:
		if (player[int(Team::Black)].pawn[7].isSelected) {
			player[int(Team::Black)].pawn[7].isSelected = false;
			someFigureSelected = false;
			break;
		}

		player[int(Team::Black)].pawn[7].isSelected = true;
		someFigureSelected = true;
		selectedFigureID = player[int(Team::Black)].pawn[7].ID;
		break;

	default:
		break;
	}
	
}

void start()
{
  worldRenderer.init();
  

  Texture2D* figuresTex =
	  worldRenderer.add_texture(new Texture2D(project_resources_path("figures.png"), RGBA));

  Texture2D* backgroundTex =
	  worldRenderer.add_texture(new Texture2D(project_resources_path("Background.png"), RGB));

  Texture2D* tableTex =
	worldRenderer.add_texture(new Texture2D(project_resources_path("Table.png"), RGB));

  Texture2D* mouseTex =
	  worldRenderer.add_texture(new Texture2D(project_resources_path("Mouse.png"), RGBA));

  Texture2D* selectTex =
	  worldRenderer.add_texture(new Texture2D(project_resources_path("Select.png"), RGB));
  
  constexpr int FigureCount = 6;
  float figureWidth = 1.f/FigureCount, figureHeight =  1.f/2.f;
  vec2 figureSize(figureWidth, figureHeight);

  /*Define all figures to players*/
  {
	  player[int(Team::White)].team = Team::White;

	  player[int(Team::White)].king = Figure{ Sprite(figuresTex, vec2(0              , 0), figureSize), Transform2D(vec2(1.15 + 2 * (0), 1 + 2 * (-4)), vec2(1)), ChessFigure::King,		Team::White };
	  player[int(Team::White)].king.x = 0;
	  player[int(Team::White)].king.y = -4;
	  tableMap.tableMap[player[int(Team::White)].king.x + 4][player[int(Team::White)].king.y + 4] = int(ChessFigure::King);
	  tableMap.figureID[player[int(Team::White)].king.x + 4][player[int(Team::White)].king.y + 4] = player[int(Team::White)].king.ID = 1;


	  player[int(Team::White)].queen = Figure{ Sprite(figuresTex, vec2(figureWidth, 0), figureSize),	  Transform2D(vec2(1.05 + 2 * (-1), 1 + 2 * (-4)), vec2(1)), ChessFigure::Queen,	Team::White };
	  player[int(Team::White)].queen.x = -1;
	  player[int(Team::White)].queen.y = -4;
	  tableMap.tableMap[player[int(Team::White)].queen.x + 4][player[int(Team::White)].queen.y + 4] = int(ChessFigure::Queen);
	  tableMap.figureID[player[int(Team::White)].queen.x + 4][player[int(Team::White)].queen.y + 4] = player[int(Team::White)].queen.ID = 2;

	  player[int(Team::White)].bishop[0] = Figure{ Sprite(figuresTex, vec2(3 * figureWidth, 0), figureSize), Transform2D(vec2(0.84 + 2 * (-2), 1 + 2 * (-4)), vec2(1)), ChessFigure::Bishop,	Team::White };
	  player[int(Team::White)].bishop[0].x = -2;
	  player[int(Team::White)].bishop[0].y = -4;
	  tableMap.tableMap[player[int(Team::White)].bishop[0].x + 4][player[int(Team::White)].bishop[0].y + 4] = int(ChessFigure::Bishop);
	  tableMap.figureID[player[int(Team::White)].bishop[0].x + 4][player[int(Team::White)].bishop[0].y + 4] = player[int(Team::White)].bishop[0].ID = 3;

	  player[int(Team::White)].bishop[1] = Figure{ Sprite(figuresTex, vec2(3 * figureWidth, 0), figureSize), Transform2D(vec2(0.84 + 2 * (1), 1 + 2 * (-4)), vec2(1)), ChessFigure::Bishop,	Team::White };
	  player[int(Team::White)].bishop[1].x = 1;
	  player[int(Team::White)].bishop[1].y = -4;
	  tableMap.tableMap[player[int(Team::White)].bishop[1].x + 4][player[int(Team::White)].bishop[1].y + 4] = int(ChessFigure::Bishop);
	  tableMap.figureID[player[int(Team::White)].bishop[1].x + 4][player[int(Team::White)].bishop[1].y + 4] = player[int(Team::White)].bishop[1].ID = 4;


	  player[int(Team::White)].rook[0] = Figure{ Sprite(figuresTex, vec2(2 * figureWidth, 0), figureSize), Transform2D(vec2(0.95 + 2 * (-4), 1 + 2 * (-4)), vec2(1)), ChessFigure::Rook,		Team::White };
	  player[int(Team::White)].rook[0].x = -4;
	  player[int(Team::White)].rook[0].y = -4;
	  tableMap.tableMap[player[int(Team::White)].rook[0].x + 4][player[int(Team::White)].rook[0].y + 4] = int(ChessFigure::Rook);
	  tableMap.figureID[player[int(Team::White)].rook[0].x + 4][player[int(Team::White)].rook[0].y + 4] = player[int(Team::White)].rook[0].ID = 5;


	  player[int(Team::White)].rook[1] = Figure{ Sprite(figuresTex, vec2(2 * figureWidth, 0), figureSize), Transform2D(vec2(0.95 + 2 * (3), 1 + 2 * (-4)), vec2(1)), ChessFigure::Rook,		Team::White };
	  player[int(Team::White)].rook[1].x = 3;
	  player[int(Team::White)].rook[1].y = -4;
	  tableMap.tableMap[player[int(Team::White)].rook[1].x + 4][player[int(Team::White)].rook[1].y + 4] = int(ChessFigure::Rook);
	  tableMap.figureID[player[int(Team::White)].rook[1].x + 4][player[int(Team::White)].rook[1].y + 4] = player[int(Team::White)].rook[1].ID = 6;

	  player[int(Team::White)].knight[0] = Figure{ Sprite(figuresTex, vec2(4 * figureWidth, 0), figureSize), Transform2D(vec2(0.7 + 2 * (-3), 1 + 2 * (-4)), vec2(1)), ChessFigure::Knight,	Team::White };
	  player[int(Team::White)].knight[0].x = -3;
	  player[int(Team::White)].knight[0].y = -4;
	  tableMap.tableMap[player[int(Team::White)].knight[0].x + 4][player[int(Team::White)].knight[0].y + 4] = int(ChessFigure::Knight);
	  tableMap.figureID[player[int(Team::White)].knight[0].x + 4][player[int(Team::White)].knight[0].y + 4] = player[int(Team::White)].knight[0].ID = 7;

	  player[int(Team::White)].knight[1] = Figure{ Sprite(figuresTex, vec2(4 * figureWidth, 0), figureSize), Transform2D(vec2(0.7 + 2 * (2), 1 + 2 * (-4)), vec2(1)), ChessFigure::Knight,	Team::White };
	  player[int(Team::White)].knight[1].x = 2;
	  player[int(Team::White)].knight[1].y = -4;
	  tableMap.tableMap[player[int(Team::White)].knight[1].x + 4][player[int(Team::White)].knight[1].y + 4] = int(ChessFigure::Knight);
	  tableMap.figureID[player[int(Team::White)].knight[1].x + 4][player[int(Team::White)].knight[1].y + 4] = player[int(Team::White)].knight[1].ID = 8;


	  for (int i = 0; i < 8; i++) {
		  player[int(Team::White)].pawn[i] = Figure{ Sprite(figuresTex, vec2(5 * figureWidth, 0), figureSize), Transform2D(vec2(0.65 + 2 * (-4 + i), 1 + 2 * (-3)), vec2(1)), ChessFigure::Pawn,		Team::White };
		  player[int(Team::White)].pawn[i].x = -4 + i;
		  player[int(Team::White)].pawn[i].y = -3;
		  tableMap.tableMap[player[int(Team::White)].pawn[i].x + 4][player[int(Team::White)].pawn[i].y + 4] = int(ChessFigure::Pawn);
		  tableMap.figureID[player[int(Team::White)].pawn[i].x + 4][player[int(Team::White)].pawn[i].y + 4] = player[int(Team::White)].pawn[i].ID = 9 + i;
	  }



	  player[int(Team::Black)].team = Team::Black;

	  player[int(Team::Black)].king = Figure{ Sprite(figuresTex, vec2(0              , figureHeight), figureSize), Transform2D(vec2(1.15 + 2 * (0), 1 + 2 * (3)), vec2(1)), ChessFigure::King,		Team::Black };
	  player[int(Team::Black)].king.x = 0;
	  player[int(Team::Black)].king.y = 3;
	  tableMap.tableMap[player[int(Team::Black)].king.x + 4][player[int(Team::Black)].king.y + 4] = (-1) * int(ChessFigure::King);
	  tableMap.figureID[player[int(Team::Black)].king.x + 4][player[int(Team::Black)].king.y + 4] = player[int(Team::Black)].king.ID = 16 + 1;

	  player[int(Team::Black)].queen = Figure{ Sprite(figuresTex, vec2(figureWidth    , figureHeight), figureSize), Transform2D(vec2(1.05 + 2 * (-1), 1 + 2 * (3)), vec2(1)), ChessFigure::Queen,		Team::Black };
	  player[int(Team::Black)].queen.x = -1;
	  player[int(Team::Black)].queen.y = 3;
	  tableMap.tableMap[player[int(Team::Black)].queen.x + 4][player[int(Team::Black)].queen.y + 4] = (-1) * int(ChessFigure::Queen);
	  tableMap.figureID[player[int(Team::Black)].queen.x + 4][player[int(Team::Black)].queen.y + 4] = player[int(Team::Black)].queen.ID = 16 + 2;

	  player[int(Team::Black)].bishop[0] = Figure{ Sprite(figuresTex, vec2(3 * figureWidth, figureHeight), figureSize), Transform2D(vec2(0.84 + 2 * (-2), 1 + 2 * (3)), vec2(1)), ChessFigure::Bishop,	Team::Black };
	  player[int(Team::Black)].bishop[0].x = -2;
	  player[int(Team::Black)].bishop[0].y = 3;
	  tableMap.tableMap[player[int(Team::Black)].bishop[0].x + 4][player[int(Team::Black)].bishop[0].y + 4] = (-1) * int(ChessFigure::Bishop);
	  tableMap.figureID[player[int(Team::Black)].bishop[0].x + 4][player[int(Team::Black)].bishop[0].y + 4] = player[int(Team::Black)].bishop[0].ID = 16 + 3;

	  player[int(Team::Black)].bishop[1] = Figure{ Sprite(figuresTex, vec2(3 * figureWidth, figureHeight), figureSize), Transform2D(vec2(0.84 + 2 * (1), 1 + 2 * (3)), vec2(1)), ChessFigure::Bishop,	Team::Black };
	  player[int(Team::Black)].bishop[1].x = 1;
	  player[int(Team::Black)].bishop[1].y = 3;
	  tableMap.tableMap[player[int(Team::Black)].bishop[1].x + 4][player[int(Team::Black)].bishop[1].y + 4] = (-1) * int(ChessFigure::Bishop);
	  tableMap.figureID[player[int(Team::Black)].bishop[1].x + 4][player[int(Team::Black)].bishop[1].y + 4] = player[int(Team::Black)].bishop[1].ID = 16 + 4;

	  player[int(Team::Black)].rook[0] = Figure{ Sprite(figuresTex, vec2(2 * figureWidth, figureHeight), figureSize), Transform2D(vec2(0.95 + 2 * (-4), 1 + 2 * (3)), vec2(1)), ChessFigure::Rook,		Team::Black };
	  player[int(Team::Black)].rook[0].x = -4;
	  player[int(Team::Black)].rook[0].y = 3;
	  tableMap.tableMap[player[int(Team::Black)].rook[0].x + 4][player[int(Team::Black)].rook[0].y + 4] = (-1) * int(ChessFigure::Rook);
	  tableMap.figureID[player[int(Team::Black)].rook[0].x + 4][player[int(Team::Black)].rook[0].y + 4] = player[int(Team::Black)].rook[0].ID = 16 + 5;

	  player[int(Team::Black)].rook[1] = Figure{ Sprite(figuresTex, vec2(2 * figureWidth, figureHeight), figureSize), Transform2D(vec2(0.95 + 2 * (3), 1 + 2 * (3)), vec2(1)), ChessFigure::Rook,		Team::Black };
	  player[int(Team::Black)].rook[1].x = 3;
	  player[int(Team::Black)].rook[1].y = 3;
	  tableMap.tableMap[player[int(Team::Black)].rook[1].x + 4][player[int(Team::Black)].rook[1].y + 4] = (-1) * int(ChessFigure::Rook);
	  tableMap.figureID[player[int(Team::Black)].rook[1].x + 4][player[int(Team::Black)].rook[1].y + 4] = player[int(Team::Black)].rook[1].ID = 16 + 6;

	  player[int(Team::Black)].knight[0] = Figure{ Sprite(figuresTex, vec2(4 * figureWidth, figureHeight), figureSize), Transform2D(vec2(0.7 + 2 * (-3), 1 + 2 * (3)), vec2(1)), ChessFigure::Knight,	Team::Black };
	  player[int(Team::Black)].knight[0].x = -3;
	  player[int(Team::Black)].knight[0].y = 3;
	  tableMap.tableMap[player[int(Team::Black)].knight[0].x + 4][player[int(Team::Black)].knight[0].y + 4] = (-1) * int(ChessFigure::Knight);
	  tableMap.figureID[player[int(Team::Black)].knight[0].x + 4][player[int(Team::Black)].knight[0].y + 4] = player[int(Team::Black)].knight[0].ID = 16 + 7;

	  player[int(Team::Black)].knight[1] = Figure{ Sprite(figuresTex, vec2(4 * figureWidth, figureHeight), figureSize), Transform2D(vec2(0.7 + 2 * (2), 1 + 2 * (3)), vec2(1)), ChessFigure::Knight,	Team::Black };
	  player[int(Team::Black)].knight[1].x = 2;
	  player[int(Team::Black)].knight[1].y = 3;
	  tableMap.tableMap[player[int(Team::Black)].knight[1].x + 4][player[int(Team::Black)].knight[1].y + 4] = (-1) * int(ChessFigure::Knight);
	  tableMap.figureID[player[int(Team::Black)].knight[1].x + 4][player[int(Team::Black)].knight[1].y + 4] = player[int(Team::Black)].knight[1].ID = 16 + 8;

	  for (int i = 0; i < 8; i++) {
		  player[int(Team::Black)].pawn[i] = Figure{ Sprite(figuresTex, vec2(5 * figureWidth, figureHeight), figureSize), Transform2D(vec2(0.65 + 2 * (-4 + i), 1 + 2 * (2)), vec2(1)), ChessFigure::Pawn,		Team::Black };
		  player[int(Team::Black)].pawn[i].x = -4 + i;
		  player[int(Team::Black)].pawn[i].y = 2;
		  tableMap.tableMap[player[int(Team::Black)].pawn[i].x + 4][player[int(Team::Black)].pawn[i].y + 4] = (-1) * int(ChessFigure::Pawn);
		  tableMap.figureID[player[int(Team::Black)].pawn[i].x + 4][player[int(Team::Black)].pawn[i].y + 4] = player[int(Team::Black)].pawn[i].ID = 16 + 9 + i;
	  }
  }

	// Draw Map
	for (int j = 7; j >= 0; j--) {
		for (int i = 0; i < 8; i++) {
			std::cout << tableMap.tableMap[i][j] << " ";
		}
		std::cout << std::endl;
	}
	// Draw Map
	for (int j = 7; j >= 0; j--) {
		for (int i = 0; i < 8; i++) {
			std::cout << tableMap.figureID[i][j] << " ";
		}
		std::cout << std::endl;
	}



  backgroundS = Sprite(backgroundTex, false, false);
  backgroundT = Transform2D(vec2(0), vec2(1536/100.0, 864/100.0));

  tableS = Sprite(tableTex, false, false);
  tableT = Transform2D(vec2(0.0f), vec2(8.0, 8.0));

  mouseS = Sprite(mouseTex, false, false);
  mouseT = Transform2D(vec2(0.0f), vec2(0.5f,0.5f));

  selectS = Sprite(selectTex, false, false);
  selectT = Transform2D(vec2(0.0f), vec2(1.0f));



  worldRenderer.spriteShader = get_shader("standart_sprite");
  //worldRenderer.backgroundShader = get_shader("test_sprite");

  Resolution r = Application::get_context().get_screen_resolution();
  worldRenderer.resolution = vec2(r.x, r.y);
  std::cout << "Screen resolution: " << r.x << " " << r.y << std::endl;

  float orthoScale = 1.f/100.f;//100 pixel per unit
  cameraProjection = mat3(0.f);
  cameraProjection[0][0] = 1.f / r.x;
  cameraProjection[1][1] = 1.f / r.y;


  cameraTransform = Transform2D(vec2(0), vec2(orthoScale));

}

// cout matrix
//cout << cameraProjection[0][0] << "      " << cameraProjection[0][1] << "      " << cameraProjection[0][2] << "      " << std::endl;
//cout << cameraProjection[1][0] << "      " << cameraProjection[1][1] << "      " << cameraProjection[1][2] << "      " << std::endl;
//cout << cameraProjection[2][0] << "      " << cameraProjection[2][1] << "      " << cameraProjection[2][2] << "      " << std::endl;


void update()
{
  //logic
  worldRenderer.screenToWorld = cameraTransform.get_matrix();
  mousePos = Input::get_mouse_position();
  tableT.position = vec2(0, 0);
  mouseT.position = worldRenderer.screen_to_world(mousePos.x+10, mousePos.y+8);
  
  // write map info for players
  for (int i = 0; i < 8; i++)
	  for (int j = 0; j < 8; j++) {
		  player[int(Team::White)].tableMap[i][j] = tableMap.tableMap[i][j];
		  player[int(Team::Black)].tableMap[i][j] = tableMap.tableMap[i][j];
		  player[int(Team::White)].figureID[i][j] = tableMap.figureID[i][j];
		  player[int(Team::Black)].figureID[i][j] = tableMap.figureID[i][j];
	  }

  // if figure is selected

  //render
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  mat3 viewProjection = cameraProjection * glm::inverse(cameraTransform.get_matrix());
  worldRenderer.spriteShader.use();
  glEnable(GL_BLEND); 
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  



  // BACKGROUND
  backgroundS.texture->bind(worldRenderer.spriteShader, "sprite", 0);
  worldRenderer.spriteShader.set_mat3x3("trasformViewProjection", viewProjection * backgroundT.get_matrix());
  worldRenderer.spriteShader.set_vec4("uvOffsetScale", vec4(vec2(0,0), vec2(1,1) ));
  worldRenderer.spriteShader.set_vec4("color", vec4(1.f));
  worldRenderer.spriteVao.render();

  // TABLE
  tableS.texture->bind(worldRenderer.spriteShader, "sprite", 0);
  worldRenderer.spriteShader.set_mat3x3("trasformViewProjection", viewProjection * tableT.get_matrix());
  worldRenderer.spriteShader.set_vec4("uvOffsetScale", vec4(vec2(0, 0), vec2(1, 1)));
  worldRenderer.spriteShader.set_vec4("color", vec4(1.f));
  worldRenderer.spriteVao.render();

  // RED SELECT
  Transform2D checkSelect = worldRenderer.screen_to_world(mousePos.x, mousePos.y);
  selectT.position = vec2(2 * (floor((checkSelect.position.x ) / 2.)) + 1, 2 * (floor((checkSelect.position.y) / 2.)) + 1);
  selectS.texture->bind(worldRenderer.spriteShader, "sprite", 0);
  worldRenderer.spriteShader.set_mat3x3("trasformViewProjection", viewProjection * selectT.get_matrix());
  worldRenderer.spriteShader.set_vec4("uvOffsetScale", vec4(vec2(0, 0), vec2(1, 1)));
  worldRenderer.spriteShader.set_vec4("color", vec4(1.0f,0.f,0.f,0.6f));
  worldRenderer.spriteVao.render();

  // DRAW FIGURES
  player[int(Team::White)].drawFigures(viewProjection, worldRenderer);
  player[int(Team::Black)].drawFigures(viewProjection, worldRenderer);


  // MOUSE
  mouseS.texture->bind(worldRenderer.spriteShader, "sprite", 0);
  worldRenderer.spriteShader.set_mat3x3("trasformViewProjection", viewProjection * mouseT.get_matrix());
  worldRenderer.spriteShader.set_vec4("uvOffsetScale", vec4(vec2(0, 0), vec2(1, 1)));
  worldRenderer.spriteShader.set_vec4("color", vec4(1.f));
  worldRenderer.spriteVao.render();
  
}

void imgui_update()
{

}

void before_exit_game()
{

}