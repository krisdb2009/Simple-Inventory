<?php
// Cedar Point 2016 // Dylan Bickerstaff // CFIT Inventory
$error = '';
$success = '';
if(isset($_POST['add']) || isset($_POST['remove'])) {
    if(isset($_POST['add']) && isset($_POST['category']) && !empty($_POST['category'])) {
        $cats = loadDB('categories');
        foreach($cats as $val) {
            if($val == $_POST['category']) {
                $error = 'Category Already Exists';
                break;
            }
        }
        if(empty($error)) {
            $cats[uniqid()] = $_POST['category'];
            putDB($cats, 'categories');
            $success = 'Added Success';
        }
    }
    if(isset($_POST['remove']) && isset($_POST['category']) && !empty($_POST['category'])) {
        $cats = loadDB('categories');
        foreach($cats as $id => $name) {
            if($_POST['category'] == $name) {
                unset($cats[$id]);
                foreach(listDB('items\\'.$id) as $itemid) {
                    unlink('./DB/static/'.loadDB('items\\'.$id.'\\'.$itemid)['img']);
                    dropDB('items\\'.$id.'\\'.$itemid);
                }
                @rmdir('./DB/items/'.$id.'/');
                $success = 'Removed';
                $error = '';
                break;
            } else {
                $error = 'Not Found';
            }
        }
        putDB($cats, 'categories');
    }
}
?>
<html>
    <head>
        <title>CFIT Inventory</title>
        <link rel="stylesheet" type="text/css" href="static/style.css">
        <meta content='width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=0' name='viewport' />
    </head>
    <body class="editcats textborder tacenter">
        <h1>Input a category to add or remove.</h1>
        <h2><?php echo $error; ?></h2>
        <h3><?php echo $success; ?></h3>
        <form method="post">
            <input class="inp" type="text" placeholder="Category Name" name="category"/>
            <button class="button textborder cbu" type="submit" name="add">Add</button><button class="button textborder cbu" type="submit" name="remove">Remove</button>
            <a class="button cbu" href="./?act=ccategor">Back</a>
        </form>
    </body>
</html>