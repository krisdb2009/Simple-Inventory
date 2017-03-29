<html>
    <head>
        <title>CFIT Inventory</title>
        <link rel="stylesheet" type="text/css" href="static/style.css">
        <meta content='width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=0' name='viewport' />
        <script>
        var keys = '';
        document.onkeydown = function(e) {
            e = e || window.event;
            if(e.key == 'Enter') {
                window.location = './?act=scanner&code='+keys;
            } else {
                keys = keys+e.key;
            }
        };
        </script>
    </head>
    <body class="ccategor textborder tacenter">
        <a class="button add ttl" href="./?act=editcats">Edit</a>
        <a class="button cat ttl" href="./">Select All</a><br><?php
        $cats = loadDB('categories');
        natcasesort($cats);
        foreach($cats as $id => $name) {
            echo '<a class="button cat" href="?cat='.$id.'">'.$name.'</a>';
        }
        ?>
    </body>
<html>