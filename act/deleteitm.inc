<?php
//Cedar Point//Dylan Bickerstaff//2016//CFIT Inventory
if(isset($_GET['cat']) && isset($_GET['item']) && isset($_POST['yes'])) {
    $item = loadDB('items\\'.$_GET['cat'].'\\'.$_GET['item']);
    if(!empty($item)) {
        dropDB('items\\'.$_GET['cat'].'\\'.$_GET['item']);
        unlink('./DB/static/'.$item['img']);
    }
    header('location: ./?cat='.$_SESSION['cat']);
    exit;
}
?>
<html>
    <head>
        <title>CFIT Inventory</title>
        <link rel="stylesheet" type="text/css" href="static/style.css">
        <meta content='width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=0' name='viewport' />
    </head>
    <body class="deleteitm textborder tacenter">
        <h1>ARE YOU SURE YOU WANT TO DELETE THIS ITEM?</h1>
        <form method="post">
            <button class="button yes" name="yes" type="submit">Yes</button><a class="button" href="./">No</a>
        </form>
    </body>
</html>