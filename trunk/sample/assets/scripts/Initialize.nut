class Character
{
	div = null;
	sprites = null;
	
	velocity = Rocket.Vector2f(0.0, 0.0);
	position = Rocket.Vector2f(0.0, 0.0);
	
	moveUp = false;
	moveLeft = false;
	moveRight = false;
	
	delta = 0.0;
	
	aceleration = 1000.0;
	deaceleration = 500.0;
	maxSpeed = 400.0;
	
	sprites = {};
	
	function OnConstruct()
	{
	}
	
	function CreateDefaultSpriteDefinition()
	{
		return { set = false, offset = { x = 0.0, y = 0.0}};
	}
	
	constructor(game)
	{
		this.div = game.gfx.CreateElement("div");
		this.div.SetClass("character", true);
		
		
		sprites.Front <- CreateDefaultSpriteDefinition();
		sprites.FrontWalkingA <- CreateDefaultSpriteDefinition();
		sprites.FrontWalkingB <- CreateDefaultSpriteDefinition();
		
		sprites.Left <- CreateDefaultSpriteDefinition();
		sprites.LeftWalkingA <- CreateDefaultSpriteDefinition();
		sprites.LeftWalkingB <- CreateDefaultSpriteDefinition();
		
		sprites.Back <- CreateDefaultSpriteDefinition();
		sprites.BackWalkingA <- CreateDefaultSpriteDefinition();
		sprites.BackWalkingB <- CreateDefaultSpriteDefinition();
		
		sprites.Right <- CreateDefaultSpriteDefinition();
		sprites.RightWalkingA <- CreateDefaultSpriteDefinition();
		sprites.RightWalkingB <- CreateDefaultSpriteDefinition();
		
		OnConstruct();
	}
	
	function ApplyPosition()
	{
		position += velocity * delta;
	
		this.div.style.bottom = position.y.tostring();
		this.div.style.left = position.x.tostring();
	}
	
	function Tick(delta)
	{
		this.delta = delta;
		
		if (moveLeft || moveRight)
		{
			if (moveRight)
			{
				if (velocity.x <= maxSpeed)
				{
					velocity.x += aceleration * delta;
				}
			}
			else if (moveLeft)
			{
				if (velocity.x >= -maxSpeed)
				{
					velocity.x += -aceleration * delta;
				}
	
			}
		}
		else
		{
			if (velocity.x > 0.0)
			{
				velocity.x -= deaceleration * delta;
			}
			else if (velocity.x < 0.0)
			{
				velocity.x += deaceleration * delta;
			}
		}
		
		
		ApplyPosition();
	}
}



class PlayerCharacter extends Character
{	
	function OnConstruct()
	{
		print("\nPlayerCharacter Created\n");
	}

	function OnKeydown()
	{
		switch(event.GetParameters().key_identifier.tointeger())
		{
			case Rocket.KeyIdentifier.LEFT:
				moveLeft = true;
				break;
			case Rocket.KeyIdentifier.RIGHT:
				moveRight = true;
				break;
			case Rocket.KeyIdentifier.UP:
				moveUp = true;
				break;
		};
	}
	
	function OnKeyup()
	{
		switch(event.GetParameters().key_identifier.tointeger())
		{
			case Rocket.KeyIdentifier.LEFT:
				moveLeft = false;
				break;
			case Rocket.KeyIdentifier.RIGHT:
				moveRight = false;
				break;
			case Rocket.KeyIdentifier.UP:
				moveUp = false;
				break;
		};
	}
}

class World
{
	game = null;
	div = null;
	characters = [];
	
	constructor(game)
	{
		this.game = game;
		this.div = this.game.gfx.GetElementById("background");
		
		this.div.AddEventListener("mousemove", "game.world.test();", true);
	}
	
	function test()
	{
		local left = this.div.style.left.tointeger();
		
		if (left >= -896)
			this.div.style.left = left - 1;
	}
	
	function AddCharacter(character, follow)
	{
		this.characters.push({ obj = character, follow = follow });
		this.div.AppendChild(character.div);
	}
};

class SampleGame
{
	//Members
	context = null;
	world = null;
	gfx = null;
	
	playerCharacter = null;
	
	//Methods
	function Tick(delta)
	{
		//world.Tick();
		playerCharacter.Tick(delta);
	
		this.context.Update();
		this.context.Render();
	}
	
	function initialize()
	{
		this.context = Rocket.Context("SquirrelGame", Rocket.Vector2i(1024, 768));
		
		this.gfx = this.game.context.LoadDocument(AssetDir("elements/game.rml"));
		
		this.world = World(this);
		
		this.gfx.Show();
		
		//Now lets add a character into the world (background)
		
		this.playerCharacter = PlayerCharacter(this);
		this.world.AddCharacter(this.playerCharacter, true);
		
		this.gfx.AddEventListener("keydown", "game.keydown();", true);
		this.gfx.AddEventListener("keyup", "game.keyup();", true);
		
		print("\nSampleGame Initialized\n");
	}
	
	function keydown()
	{	
		playerCharacter.OnKeydown();
	
		switch(event.GetParameters().key_identifier)
		{
			case Rocket.KeyIdentifier.LEFT:
				break;
			case Rocket.KeyIdentifier.RIGHT:
				break;
		};
	}
	
	function keyup()
	{
		playerCharacter.OnKeyup();
		switch(event.GetParameters().key_identifier)
		{
			case Rocket.KeyIdentifier.LEFT:
				break;
			case Rocket.KeyIdentifier.RIGHT:
				break;
		};
	}
};

game <- SampleGame();
game.initialize();

Tick <- function(delta)
{
	game.Tick(delta);
}