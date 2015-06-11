# WebGL Article Viewer
Computer Graphics class term project.

Implemented Article Viewer with WebGL

implemented leftSide.html, main.html
bitmap resources are in 'frame' directory and 'sum' directory

You will see some pictures on the left side when you open the main.html.
Left side is for the graphical menu and right side is for the articles.

At the first state, user will see the up and down arrows and . there is one big picture at center of left area, and there are two small pictures above and below.
That state is 'selecting category' state. When user clicks direction arrow, the center category will change(used translate and scale)

If the user clicks big center picture(category select), that picture will turn around (used rotate) and sub items in that category will show up.
If user put the cursor on an item, picture will be zoomed-in and the image will float around(it won't get out the area). User can zoom-in and out with mouse wheel but it won't work in firefox (works in IE and chrome).

If the user clicks the item, the article of that item will show up on the right side area.

User can go back to the 'selecting category' state by clicking any left side area except pictures.