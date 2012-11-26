local doc = context.LoadDocument("./assets/demo.rml");

doc.ShowFocus(Rocket.ElementDocument.FOCUS);

doc.SetId("demodoc");

print(doc.GetId());

local content = doc.GetElementById("content");

content.SetClass("hideclass", true);


local handle = doc.GetElementById("handle");

print("\nabsX = " + handle.GetAbsoluteLeft() + " absY = " + handle.GetAbsoluteTop() + "\n");

print("\nGetClient__ = " + 
	handle.GetClientLeft() + " " +
	handle.GetClientTop() + " " +
	handle.GetClientWidth() + " " +
	handle.GetClientHeight() + " \n"
);

//if the element is not found then returns itself
if (handle.GetId() == doc.GetId())
{
	print("\nGetElementById failed\n");
}

handle.SetClassNames("class1 class2 class3");

print("\n" + handle.GetClassNames() + "\n");

print("\n" + handle.GetAddress(true) + "\n");

content.AppendChild(handle);

print(doc.RemoveChild(content));
//print(doc.ReplaceChild(content, doc));


doc = context.LoadDocument("./");

print(doc.GetTagName());