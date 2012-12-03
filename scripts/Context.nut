context <- Rocket.Context("ScriptsContext");

//local cursor = context.LoadMouseCursor("./assets/cursor.rml");

//cursor.Show();

try {
	//local context = Rocket.Context("ScriptsContext", Rocket.Vector2i(1024, 768));

} catch (e)
{
	print("\nHandled Exception: " + e + "\n");
}

function printContextDimensions()
{
	print("\nContext '" + context.GetName() + "' Dimensions: x = " 
		+ context.GetDimensions().x 
		+ " y = " + context.GetDimensions().y + "\n");
}

printContextDimensions();

context.SetDimensions(Rocket.Vector2i(1024, 768));

printContextDimensions();


