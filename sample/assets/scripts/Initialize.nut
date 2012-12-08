class Character
{
	div = null;
	sprites = null;
	
	velocity = Rocket.Vector2f(0.0, 0.0);
	position = Rocket.Vector2f(0.0, 0.0);
	
	moveUp = false;
	moveLeft = false;
	moveRight = false;
	
	moving = false;
	
	delta = 0.0;
	
	aceleration = 400.0;
	deaceleration = 200.0;
	maxSpeed = 200.0;
	
	lastClass = "";
	
	step = 0;
	stepTime = 0;
	
	spriteDiv = null;
	sprites = {};
	
	function OnConstruct()
	{
	}
	
	function CreateDefaultSpriteDefinition()
	{
		return { set = false, cssClass = "" };
	}
	
	constructor(game)
	{
		this.div = game.gfx.CreateElement("div");
		this.div.SetClass("character", true);
		
		this.spriteDiv = game.gfx.CreateElement("div");
		this.spriteDiv.SetClass("sprite", true);
		this.div.AppendChild(spriteDiv);
		
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
	
	function OnInitialize()
	{
	}
	
	function Initialize()
	{
		this.div.SetClass(sprites.Front.cssClass, true);
		this.lastClass = sprites.Front.cssClass;
	}
	
	function SetSprite(spriteDef)
	{
		this.div.SetClass(lastClass, false);
		lastClass = spriteDef.cssClass;
		this.div.SetClass(spriteDef.cssClass, true);
	}
	
	function ApplyPosition()
	{
		position += velocity * delta;
	
		this.div.style.bottom = position.y.tointeger();
		this.div.style.left = position.x.tointeger();
	}
	
	function stepSprite(a, b, c)
	{
		switch (step)
		{
			case 0: SetSprite(a); break;
			case 1: SetSprite(b); break;
			case 2: SetSprite(c); break;
		}
	}
	
	function GetCurrentVelocityX()
	{
		if (velocity.x < 0.0)
		{
			return -velocity.x;
		}
		return velocity.x;
	}
	
	function Tick(delta)
	{
		this.delta = delta;
	
		local elapsed = GetElapsedTime();
		if (stepTime <= elapsed)
		{
			step += 1;
			if (step > 2)
			{
				step = 0;
			}
			
			stepTime = elapsed + 0.2;
		}
		
		if (moveLeft || moveRight)
		{
			moving = true;
			if (moveRight)
			{
				if (velocity.x <= maxSpeed)
				{
					velocity.x += aceleration * delta;
				}
				stepSprite(sprites.Right, sprites.RightWalkingA, sprites.RightWalkingB);
			}
			else if (moveLeft)
			{
				if (velocity.x >= -maxSpeed)
				{
					velocity.x += -aceleration * delta;
				}
				stepSprite(sprites.Left, sprites.LeftWalkingA, sprites.LeftWalkingB);
			}
		}
		else
		{
			if (moving)
			{
				if (velocity.x > 0.0)
				{
					velocity.x -= deaceleration * delta;
					stepSprite(sprites.Right, sprites.RightWalkingA, sprites.RightWalkingB);
				}
				else if (velocity.x < 0.0)
				{
					velocity.x += deaceleration * delta;
					stepSprite(sprites.Left, sprites.LeftWalkingA, sprites.LeftWalkingB);
				}
				
				if (velocity.x <= 1.0 && velocity.x >= -1.0)
				{
					moving = false;
					SetSprite(sprites.Front);
				}
			}
		}
		
		if (moving)
		{
			ApplyPosition();
		}
		
	}
}



class PlayerCharacter extends Character
{	
	function OnConstruct()
	{
		print("\nPlayerCharacter Created\n");
		
		sprites.Front.set = true;
		sprites.Front.cssClass = "PlayerCharFront";
		
		sprites.Left.set = true;
		sprites.Left.cssClass = "PlayerCharLeft";
		sprites.LeftWalkingA.set = true;
		sprites.LeftWalkingA.cssClass = "PlayerCharLeftWalkA";
		sprites.LeftWalkingB.set = true;
		sprites.LeftWalkingB.cssClass = "PlayerCharLeftWalkB";
		
		sprites.Right.set = true;
		sprites.Right.cssClass = "PlayerCharRight";
		sprites.RightWalkingA.set = true;
		sprites.RightWalkingA.cssClass = "PlayerCharRightWalkA";
		sprites.RightWalkingB.set = true;
		sprites.RightWalkingB.cssClass = "PlayerCharRightWalkB";
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

class IntroCredits
{
	
	credits = null;
	switcher = null;
	switcherAlpha = 255;
	time = 0;
	
	constructor(game)
	{
		switcher = game.gfx.GetElementById("switcher");
		credits = game.gfx.GetElementById("credits");
		
		time = GetElapsedTime() + 3;
	}
	
	function Tick(delta)
	{
		switcherAlpha -= 200.5 * delta;
		if (switcherAlpha <= 0)
		{
			switcherAlpha = 0;
		}
	
		switcher.style.background_color = "rgba(0,0,0," + switcherAlpha + ")";
		
		if (time <= GetElapsedTime())
		{
			this.credits.style.display = "none";
			this.switcher.style.display = "none";
			return false;
		}
		
		return true;
	}

}

enum GameState { STATE_INTRO_CREDITS, STATE_PLAYING };

class SampleGame
{
	//Members
	context = null;
	world = null;
	gfx = null;
	introCredits = null;
	
	state = GameState.STATE_INTRO_CREDITS;
	
	playerCharacter = null;
	
	//Methods
	function Tick(delta)
	{
		//world.Tick();
		
		switch (state)
		{
			case GameState.STATE_INTRO_CREDITS:
				
				if (!introCredits.Tick(delta))
				{
					state = GameState.STATE_PLAYING;
				}
				
				break;
			case GameState.STATE_PLAYING:
				playerCharacter.Tick(delta);
				break;
		}
		
		this.context.Update();
		this.context.Render();
	}
	
	function initialize()
	{
		this.context = Rocket.Context("SquirrelGame", Rocket.Vector2i(1024, 768));
		
		this.gfx = this.game.context.LoadDocument(AssetDir("elements/game.rml"));
		
		this.world = World(this);
		
		this.gfx.Show();
		
		this.introCredits = IntroCredits(this);
		
		//Now lets add a character into the world (background)
		
		this.playerCharacter = PlayerCharacter(this);
		this.playerCharacter.Initialize();
		
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