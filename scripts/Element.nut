print("\n\n :: Element Tests :: \n\n");

try 
{
	print("Test direct instacing\n");
	local ele = Rocket.ElementDocument();
} catch (e)
{
	print("\nExecption Handled: " + e + "\n");
}

local doc = context.CreateDocument("body");

doc.Blur();
doc.Click();
doc.Focus();
print("is class set: " + doc.IsClassSet("class") + "\n");
doc.SetClass("myclass", true);
print("is class set: " + doc.IsClassSet("myclass") + "\n");
doc.SetPseudoClass("mypseudoclass", true);
print("is pseudoclass set: " + doc.IsPseudoClassSet("mypseudoclass") + "\n");

context.UnloadDocument(doc);
context.UnloadAllDocuments();

print("\nUnloaded Document tag: " + doc.GetTagName() + "\n");