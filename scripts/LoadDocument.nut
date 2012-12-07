local doc = context.LoadDocument(ASSETS_DIR + "/demo.rml");

doc.ShowFocus(Rocket.ElementDocument.FOCUS);

doc.SetId("demodoc");

print(doc.GetId());

local content = doc.GetElementById("content");

content.SetClass("hideclass", false);


local handle = doc.GetElementById("handle");

print("\nabsX = " + handle.GetAbsoluteLeft() + " absY = " + handle.GetAbsoluteTop() + "\n");

print("\nGetClient__ = " + 
	handle.GetClientLeft() + " " +
	handle.GetClientTop() + " " +
	handle.GetClientWidth() + " " +
	handle.GetClientHeight() + " \n"
);

function printOffsets(element)
{
	print("\nOffsets = " + 
		element.GetOffsetLeft() + " " +
		element.GetOffsetTop() + " " +
		element.GetOffsetWidth() + " " +
		element.GetOffsetHeight() + " \n"
	);
}

printOffsets(handle);
printOffsets(handle.GetOffsetParent());

print("\nScroll = " + 
	handle.GetScrollLeft() + " " +
	handle.GetScrollTop() + " " +
	handle.GetScrollWidth() + " " +
	handle.GetScrollHeight() + " \n"
);

print("\nOwnerDocument = " + handle.GetOwnerDocument().GetId() + "\n");
print("\nNextSiblidng = " + handle.GetNextSibling().GetId() + "\n");
print("\nPreviousSiblidng = " + handle.GetPreviousSibling().GetId() + "\n");

print("\nGetParentNode Address = " + handle.GetParentNode().GetAddress(true) + "\n");
print("\nGetParentNode Address = " + doc.GetParentNode().GetParentNode().GetAddress(true) + "\n");

//if the element is not found then returns itself
if (handle.GetId() == doc.GetId())
{
	print("\nGetElementById failed\n");
}

handle.SetClassNames("class1 class2 class3");

print("\n" + handle.GetClassNames() + "\n");

print("\n" + handle.GetAddress(true) + "\n");

//ontent.AppendChild(handle);

local next = content.GetNextSibling();



function compare(a,b)
{
	if (a.Equals(b))
	{
		print("\nEqual = true");
	}
	else
	{
		print("\nEqual = false");
	}
}


compare(next, handle);
compare(handle, handle);

handle.SetAttribute("id", Rocket.Variant("newhandle"));
print(handle.GetAttribute("id"));

print("\n" + handle.GetInnerRML() + "\n");
handle.SetInnerRML("Inner RML");


local elements = doc.GetElementsByTagName("div");

for (local i = 0; i < elements.len(); i+=1)
{
	print(" -> " + elements[i].GetId() + "\n");
}

content.style["padding"] = "2";
content.style["margin"] = "20";
print("\n Padding Top = " + content.style["padding-top"]);

local text = doc.CreateTextNode("mytextnode");

text.SetText("My Text");

handle.AppendChild(text);

handle.SetInnerRML("<span>Inner <b>RML 2</b></span>");

print("\n" + text.GetText() + "\n");