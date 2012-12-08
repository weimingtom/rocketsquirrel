class Character
{
	div = null;
	sprites = null;
	
	constructor(game)
	{
		this.div = game.gfx.CreateElement("div");
		this.div.SetClass("character", true);
	}
}



class PlayerCharacter extends Character
{
	velocity = Rocket.Vector2f(0.0, 0.0f);
	
	moveUp = false;
	moveLeft = false;
	moveRight = false;
	
	function Tick()
	{
		
	}
	
	function OnKeydown()
	{	
		switch(event.GetParameters().key_identifier)
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
		switch(event.GetParameters().key_identifier)
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
	function Tick()
	{
		//world.Tick();
		playerCharacter.Tick();
	
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
		this.gfx.AddEventListener("keydown", "game.keyup();", true);
		
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

Tick <- function()
{
	game.Tick();
}