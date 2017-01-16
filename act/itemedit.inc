<?php
//Cedar Point//Dylan Bickerstaff//2016//CFIT Inventory
$categories = loadDB('categories');
$iName = '';
$iCount = 0;
$error = '';
if(isset($_GET['cat']) && isset($_GET['item']) && !empty($_GET['cat']) && !empty($_GET['item'])) {
    $item = loadDB('items\\'.$_GET['cat'].'\\'.$_GET['item']);
    if(!empty($item)) {
        if(isset($_POST['edit'])) {
            if(isset($_POST['name']) && !empty($_POST['name'])) {
                $item['name'] = $_POST['name'];
            }
            if(isset($_POST['count']) && !empty($_POST['count'])) {
                $item['count'] = $_POST['count'];
            }
            if(isset($_FILES['photo']['name']) && !empty($_FILES['photo']['name'])) {
                if($_FILES['photo']['size'] < (1024000) && (@getimagesize($_FILES["photo"]["tmp_name"]) !== false))
                {
                    $folder = './DB/static/';
                    $ex = pathinfo($_FILES['photo']['name'], PATHINFO_EXTENSION);
                    $imgn = uniqid().'.'.$ex;
                    move_uploaded_file($_FILES['photo']['tmp_name'], $folder.$imgn);
                    unlink($folder.$item['img']);
                    $item['img'] = $imgn;
                } else {
                    $error = 'Please Select a Valid Image under 1MB';
                }
            }
            if(isset($_POST['category']) && !empty($_POST['category']) && $_POST['category'] !== $_GET['cat']) {
                dropDB('items\\'.$_GET['cat'].'\\'.$_GET['item']);
                $_GET['cat'] = $_POST['category'];
            }
            putDB($item, 'items\\'.$_GET['cat'].'\\'.$_GET['item']);
            if(empty($error)) {
                header('location: ./?act=item&cat='.$_GET['cat'].'&item='.$_GET['item']);
                exit;
            }
        }
        $iName = $item['name'];
        $iCount = $item['count'];
    } else {
        $error = 'Item Not Found';
    }
}
?>
<html>
    <head>
        <title>CFIT Inventory</title>
        <link rel="stylesheet" type="text/css" href="static/style.css">
        <meta content='width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=0' name='viewport' />
    </head>
    <body class="itemedit textborder tacenter">
        <div class="ttl">Edit: <?php echo $iName; ?><div style="color:red;"><?php echo $error; ?></div></div>
        <form enctype="multipart/form-data" method="post">
            <input class="nam" type="text" placeholder="Item Name" value="<?php echo $iName; ?>" name="name"/><br>
            <input class="num" type="number" value="<?php echo $iCount; ?>" name="count" min="0" max="999" step="1" value="0"/><select class="cat" name="category">
                <option value="" default>-Category-</option>
                <?php
                    foreach($categories as $id => $name) {
                        $sel = '';
                        if(isset($_GET['cat']) && !empty($_GET['cat']) && $_GET['cat'] == $id) {
                           $sel = 'selected';
                        }
                        echo '<option '.$sel.' value="'.$id.'">'.$name.'</option>';
                    }
                ?>
            </select><br>
            <input class="fil" accept="image/*" type="file" name="photo"/><br>
            <input type="hidden" name="edit"/>
            <button class="button textborder add">Done</button><br>
            <a class="button can" href="./?act=item&cat=<?php echo $_GET['cat'] .'&item='.$_GET['item']; ?>">Cancel</a>
        </form>
    </body>
<html>