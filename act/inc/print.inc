<?php
//Looks for $title (string) and $items with ['name'] and ['count']
$reciptCharWidth = 25;
$reciptFontSize = 16;
?>
<body style="margin:0px;">
    <script>
    window.print();
    setInterval(function() {
        history.back();
    }, 1000);
    </script>
    <img style="width:240px;height:100px;" src="static/cfit.png">
        <pre style="display:block;overflow:hidden;width:240px;font-size:<?php echo $reciptFontSize; ?>px;font-family:Lucida Console;"><?php
        $dash = '';
        while(strlen($dash) < $reciptCharWidth) {
            $dash = $dash.'-';
        }
        echo $dash."\n";
        echo $title."\n";
        echo $dash."\n\n";
        foreach($items as $arr) {
            $space = '';
            if(strlen($arr['name']) > $reciptCharWidth - 4) {
                $arr['name'] = substr($arr['name'], 0, $reciptCharWidth - 6).'...';
            }
            while(strlen($arr['name']) + strlen($space) + strlen($arr['count']) < $reciptCharWidth) {
                $space = $space.' ';
            }
            echo $arr['name'].$space.$arr['count']."\n\n";
        }
        echo "\n";
        echo $dash;
        echo "\n\n\n.";
        ?></pre>
</body>