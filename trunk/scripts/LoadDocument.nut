local doc = context.LoadDocument("./assets/demo.rml");

doc.ShowFocus(Rocket.ElementDocument.FOCUS);

print(doc.GetTagName());

doc = context.LoadDocument("./");

print(doc.GetTagName());