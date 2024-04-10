
enum class ChessFigure
{
	King = 1,
	Queen = 2,
	Bishop = 3,
	Rook = 4,
	Knight = 5,
	Pawn = 6
};
enum class Team
{
	White = 0,
	Black = 1
};

struct Figure
{
	Sprite sprite;
	Transform2D transform;
	ChessFigure type;
	Team team;
	bool isActive = true;
	bool isSelected = false;

	int x;
	int y;
	int ID;


};

class Player
{
public:
	Figure king;//ID 1
	Figure queen;//ID 2
	Figure bishop[2];//ID 3 4
	Figure rook[2];//ID 5 6
	Figure knight[2];// ID 7 8
	Figure pawn[8];// ID 9-16
	Figure dummy;

	Figure &pointer = dummy;

	Team team;

	int tableMap[8][8];
	int figureID[8][8];
	
	void drawFigures(mat3 viewProjection, WorldRenderer worldRenderer)
	{	
		if (king.isActive) {

			if (king.isSelected) {
				king.sprite.texture->bind(worldRenderer.spriteShader, "sprite", 0);
				worldRenderer.spriteShader.set_mat3x3("trasformViewProjection", viewProjection * king.transform.get_matrix());
				worldRenderer.spriteShader.set_vec4("uvOffsetScale", vec4(king.sprite.offset, king.sprite.scale));
				worldRenderer.spriteShader.set_vec4("color", vec4(0.f,0.f,1.f,1.f));
				worldRenderer.spriteVao.render();
			}
			if (king.isSelected == false) {
				king.sprite.texture->bind(worldRenderer.spriteShader, "sprite", 0);
				worldRenderer.spriteShader.set_mat3x3("trasformViewProjection", viewProjection * king.transform.get_matrix());
				worldRenderer.spriteShader.set_vec4("uvOffsetScale", vec4(king.sprite.offset, king.sprite.scale));
				worldRenderer.spriteShader.set_vec4("color", vec4(1.f));
				worldRenderer.spriteVao.render();
			}
		}
		if (queen.isActive) {

			if (queen.isSelected) {
				queen.sprite.texture->bind(worldRenderer.spriteShader, "sprite", 0);
				worldRenderer.spriteShader.set_mat3x3("trasformViewProjection", viewProjection * queen.transform.get_matrix());
				worldRenderer.spriteShader.set_vec4("uvOffsetScale", vec4(queen.sprite.offset, queen.sprite.scale));
				worldRenderer.spriteShader.set_vec4("color", vec4(0.f, 0.f, 1.f, 1.f));
				worldRenderer.spriteVao.render();
			}

			if (queen.isSelected == false) {
				queen.sprite.texture->bind(worldRenderer.spriteShader, "sprite", 0);
				worldRenderer.spriteShader.set_mat3x3("trasformViewProjection", viewProjection * queen.transform.get_matrix());
				worldRenderer.spriteShader.set_vec4("uvOffsetScale", vec4(queen.sprite.offset, queen.sprite.scale));
				worldRenderer.spriteShader.set_vec4("color", vec4(1.f));
				worldRenderer.spriteVao.render();
			}
		}
		if (bishop[0].isActive) {

			if (bishop[0].isSelected) {
				bishop[0].sprite.texture->bind(worldRenderer.spriteShader, "sprite", 0);
				worldRenderer.spriteShader.set_mat3x3("trasformViewProjection", viewProjection * bishop[0].transform.get_matrix());
				worldRenderer.spriteShader.set_vec4("uvOffsetScale", vec4(bishop[0].sprite.offset, bishop[0].sprite.scale));
				worldRenderer.spriteShader.set_vec4("color", vec4(0.f, 0.f, 1.f, 1.f));
				worldRenderer.spriteVao.render();
			}
			if (bishop[0].isSelected == false) {
				bishop[0].sprite.texture->bind(worldRenderer.spriteShader, "sprite", 0);
				worldRenderer.spriteShader.set_mat3x3("trasformViewProjection", viewProjection * bishop[0].transform.get_matrix());
				worldRenderer.spriteShader.set_vec4("uvOffsetScale", vec4(bishop[0].sprite.offset, bishop[0].sprite.scale));
				worldRenderer.spriteShader.set_vec4("color", vec4(1.f));
				worldRenderer.spriteVao.render();
			}

			
		}
		if (bishop[1].isActive) {

			if (bishop[1].isSelected) {
				bishop[1].sprite.texture->bind(worldRenderer.spriteShader, "sprite", 0);
				worldRenderer.spriteShader.set_mat3x3("trasformViewProjection", viewProjection * bishop[1].transform.get_matrix());
				worldRenderer.spriteShader.set_vec4("uvOffsetScale", vec4(bishop[1].sprite.offset, bishop[1].sprite.scale));
				worldRenderer.spriteShader.set_vec4("color", vec4(0.f, 0.f, 1.f, 1.f));
				worldRenderer.spriteVao.render();
			}
			if (bishop[1].isSelected == false) {
				bishop[1].sprite.texture->bind(worldRenderer.spriteShader, "sprite", 0);
				worldRenderer.spriteShader.set_mat3x3("trasformViewProjection", viewProjection * bishop[1].transform.get_matrix());
				worldRenderer.spriteShader.set_vec4("uvOffsetScale", vec4(bishop[1].sprite.offset, bishop[1].sprite.scale));
				worldRenderer.spriteShader.set_vec4("color", vec4(1.f));
				worldRenderer.spriteVao.render();
			}


		}
		if (rook[0].isActive) {

			if (rook[0].isSelected) {
				rook[0].sprite.texture->bind(worldRenderer.spriteShader, "sprite", 0);
				worldRenderer.spriteShader.set_mat3x3("trasformViewProjection", viewProjection * rook[0].transform.get_matrix());
				worldRenderer.spriteShader.set_vec4("uvOffsetScale", vec4(rook[0].sprite.offset, rook[0].sprite.scale));
				worldRenderer.spriteShader.set_vec4("color", vec4(0.f, 0.f, 1.f, 1.f));
				worldRenderer.spriteVao.render();
			}
			if (rook[0].isSelected == false) {
				rook[0].sprite.texture->bind(worldRenderer.spriteShader, "sprite", 0);
				worldRenderer.spriteShader.set_mat3x3("trasformViewProjection", viewProjection * rook[0].transform.get_matrix());
				worldRenderer.spriteShader.set_vec4("uvOffsetScale", vec4(rook[0].sprite.offset, rook[0].sprite.scale));
				worldRenderer.spriteShader.set_vec4("color", vec4(1.f));
				worldRenderer.spriteVao.render();
			}
		}
		if (rook[1].isActive) {

			if (rook[1].isSelected) {
				rook[1].sprite.texture->bind(worldRenderer.spriteShader, "sprite", 0);
				worldRenderer.spriteShader.set_mat3x3("trasformViewProjection", viewProjection * rook[1].transform.get_matrix());
				worldRenderer.spriteShader.set_vec4("uvOffsetScale", vec4(rook[1].sprite.offset, rook[1].sprite.scale));
				worldRenderer.spriteShader.set_vec4("color", vec4(0.f, 0.f, 1.f, 1.f));
				worldRenderer.spriteVao.render();
			}
			if (rook[1].isSelected == false) {
				rook[1].sprite.texture->bind(worldRenderer.spriteShader, "sprite", 0);
				worldRenderer.spriteShader.set_mat3x3("trasformViewProjection", viewProjection * rook[1].transform.get_matrix());
				worldRenderer.spriteShader.set_vec4("uvOffsetScale", vec4(rook[1].sprite.offset, rook[1].sprite.scale));
				worldRenderer.spriteShader.set_vec4("color", vec4(1.f));
				worldRenderer.spriteVao.render();
			}

			
		}
		if (knight[0].isActive) {

			if (knight[0].isSelected) {
				knight[0].sprite.texture->bind(worldRenderer.spriteShader, "sprite", 0);
				worldRenderer.spriteShader.set_mat3x3("trasformViewProjection", viewProjection* knight[0].transform.get_matrix());
				worldRenderer.spriteShader.set_vec4("uvOffsetScale", vec4(knight[0].sprite.offset, knight[0].sprite.scale));
				worldRenderer.spriteShader.set_vec4("color", vec4(0.f, 0.f, 1.f, 1.f));
				worldRenderer.spriteVao.render();
			}
			if (knight[0].isSelected == false) {
				knight[0].sprite.texture->bind(worldRenderer.spriteShader, "sprite", 0);
				worldRenderer.spriteShader.set_mat3x3("trasformViewProjection", viewProjection* knight[0].transform.get_matrix());
				worldRenderer.spriteShader.set_vec4("uvOffsetScale", vec4(knight[0].sprite.offset, knight[0].sprite.scale));
				worldRenderer.spriteShader.set_vec4("color", vec4(1.f));
				worldRenderer.spriteVao.render();
			}
			
		}
		if (knight[1].isActive) {

			if (knight[1].isSelected) {
				knight[1].sprite.texture->bind(worldRenderer.spriteShader, "sprite", 0);
				worldRenderer.spriteShader.set_mat3x3("trasformViewProjection", viewProjection* knight[1].transform.get_matrix());
				worldRenderer.spriteShader.set_vec4("uvOffsetScale", vec4(knight[1].sprite.offset, knight[1].sprite.scale));
				worldRenderer.spriteShader.set_vec4("color", vec4(0.f, 0.f, 1.f, 1.f));
				worldRenderer.spriteVao.render();
			}
			if (knight[1].isSelected == false) {
				knight[1].sprite.texture->bind(worldRenderer.spriteShader, "sprite", 0);
				worldRenderer.spriteShader.set_mat3x3("trasformViewProjection", viewProjection* knight[1].transform.get_matrix());
				worldRenderer.spriteShader.set_vec4("uvOffsetScale", vec4(knight[1].sprite.offset, knight[1].sprite.scale));
				worldRenderer.spriteShader.set_vec4("color", vec4(1.f));
				worldRenderer.spriteVao.render();
			}
		}
		/*pawns is Active*/
		for (int i = 0; i < 8; i++)
		{
			if (pawn[i].isActive) {

				if (pawn[i].isSelected) {
					pawn[i].sprite.texture->bind(worldRenderer.spriteShader, "sprite", 0);
					worldRenderer.spriteShader.set_mat3x3("trasformViewProjection", viewProjection* pawn[i].transform.get_matrix());
					worldRenderer.spriteShader.set_vec4("uvOffsetScale", vec4(pawn[i].sprite.offset, pawn[i].sprite.scale));
					worldRenderer.spriteShader.set_vec4("color", vec4(0.f, 0.f, 1.f, 1.f));
					worldRenderer.spriteVao.render();
				}
				if (pawn[i].isSelected == false) {
					pawn[i].sprite.texture->bind(worldRenderer.spriteShader, "sprite", 0);
					worldRenderer.spriteShader.set_mat3x3("trasformViewProjection", viewProjection* pawn[i].transform.get_matrix());
					worldRenderer.spriteShader.set_vec4("uvOffsetScale", vec4(pawn[i].sprite.offset, pawn[i].sprite.scale));
					worldRenderer.spriteShader.set_vec4("color", vec4(1.f));
					worldRenderer.spriteVao.render();
				}
			}
		}
	}
	int whatFigureIsID(int x, int y) {
		/*
		switch (tableMap[x][y]) {
		case -6: // Pawn Black
			return figureID[x][y];
			break;
		case -5: // Knight Black
			break;
		case -4: // Rook Black 
			break;
		case -3: // Bishop Black
			break;
		case -2: // Queen Black
			break;
		case -1: // King Black
			break;

		case 1:  // King White
			break;
		case 2:  // Queen White
			break;
		case 3:  // Bishop White
			break;
		case 4:  // Rook White
			break;
		case 5:  // Knight White
			break;
		case 6:  // Pawn White
			break;
		}
		*/
		return figureID[x][y];
	}
};
