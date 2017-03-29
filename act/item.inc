<?php
//Cedar Point//Dylan Bickerstaff//2016//CFIT Inventory
$iName = 'Not Found';
$iCount = 0;
$iID = '';
$iImage = '';
$cID = '';
$mindel = '-';
if(isset($_GET['cat']) && !empty($_GET['cat']) && isset($_GET['item']) && !empty($_GET['item'])) {
    $item = loadDB('items\\'.$_GET['cat'].'\\'.$_GET['item']);
    if(!empty($item)) {
        if(isset($_POST['addsub'])) {
            if(isset($_POST['add'])) {
                if(!($item['count'] >= 999)) {
                    $item['count']++;
                }
            }
            if(isset($_POST['sub'])) {
                if(!($item['count'] <= 0)) {
                    $item['count']--;
                } else {
                    header('location: ./?act=deleteitm&cat='.$_GET['cat'].'&item='.$_GET['item']);
                }
            }
            putDB($item, 'items\\'.$_GET['cat'].'\\'.$_GET['item']);
        }
        $iName = $item['name'];
        $iCount = $item['count'];
        $iImage = $item['img'];
        $iID = $_GET['item'];
        $cID = $_GET['cat'];
        if($iCount == 0) {
            $mindel = '<span class="textborder" style="color:red;">Delete</span>';
        }
    }
}
?>
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
    <body class="item textborder tacenter">
        <div class="wrap">
            <a href="./?act=itemedit&cat=<?php echo $_GET['cat']; ?>&item=<?php echo $_GET['item']; ?>" class="button edit">Edit</a>
            <div class="itm"><?php echo $iName; ?></div>
            <div style="background-image:url('./DB/static/<?php echo $iImage; ?>');" class="img"></div>
            <form method="post">
                <input type="hidden" name="addsub"/>
                <button class="button textborder sub" type="submit" name="sub"><?php echo $mindel; ?></button>
                <span class="count"><?php echo $iCount; ?></span>
                <button class="button textborder add" type="submit" name="add">+</button>
            </form>
            <a href="./?cat=<?php echo $_SESSION['cat']; ?>" class="button done">Done</a>
        </div>
    </body>
<html>