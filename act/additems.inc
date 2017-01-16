<?php
//Cedar Point//Dylan Bickerstaff//2016//CFIT Inventory
$error = '';
$success = '';
if(isset($_POST['add'])) {
    if($_POST['add'] == 'item' && isset($_POST['category']) && !empty($_POST['category']) && isset($_POST['name']) && !empty($_POST['name']) && isset($_POST['count'])) {
        if(isset($_FILES['photo']['name'])) {
            if($_FILES['photo']['size'] < (1024000) && (@getimagesize($_FILES["photo"]["tmp_name"]) !== false))
            {
                $folder = './DB/static/';
                if(!is_dir($folder)) mkdir($folder, 0777, true);
                $ex = pathinfo($_FILES['photo']['name'], PATHINFO_EXTENSION);
                $imgn = uniqid().'.'.$ex;
                move_uploaded_file($_FILES['photo']['tmp_name'], $folder.$imgn);
                $count = 0;
                if(!empty($_POST['count']) && $_POST['count'] >= 0 && $_POST['count'] <= 999) {
                    $count = $_POST['count'];
                }
                putDB(array('name' => $_POST['name'], 'img' => $imgn, 'count' => $count), 'items\\'.$_POST['category'].'\\'.uniqid());
                $success = 'Added';
            } else {
                $error = 'Please Select a Valid Image under 1MB';
            }
        }
    } else {
        $error = 'Please Fill All Forms';
    }
}
?>
<html>
    <head>
        <title>CFIT Inventory</title>
        <link rel="stylesheet" type="text/css" href="static/style.css">
        <meta content='width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=0' name='viewport' />
    </head>
    <body class="additems textborder tacenter">
        <div class="ttl">Add Items <div style="color:red;"><?php echo $error; ?></div><div style="color:green;"><?php echo $success; ?></div></div>
        <form enctype="multipart/form-data" method="post">
            <input class="nam" type="text" placeholder="Item Name" name="name"/><br>
            <input class="num" type="number" name="count" min="0" max="999" step="1" value="0"/><select class="cat" name="category">
                <option value="" default>-Category-</option>
                <?php
                    foreach(loadDB('categories') as $id => $name) {
                        $sel = '';
                        if(isset($_GET['cat']) && !empty($_GET['cat']) && $_GET['cat'] == $id) {
                           $sel = 'selected';
                        }
                        echo '<option '.$sel.' value="'.$id.'">'.$name.'</option>';
                    }
                ?>
            </select><br>
            <input class="fil" accept="image/*" type="file" name="photo"/><br>
            <input type="hidden" name="add" value="item"/>
            <button class="button textborder add">Add</button><br>
            <a class="button can" href="./?cat=<?php echo $_GET['cat']; ?>">Done</a>
        </form>
    </body>
<html>