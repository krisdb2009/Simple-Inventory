<?php
//Cedar Point//Dylan Bickerstaff//2016//CFIT Inventory
    $title = 'All Categories';
    $items = array();
    if(isset($_GET['cat']) && !empty($_GET['cat'])) {
        $cats = loadDB('categories');
        if(isset($cats[$_GET['cat']])) {
            $categoryName = $cats[$_GET['cat']];
            foreach(listDB('items\\'.$_GET['cat']) as $id) {
                $items[$id] = loadDB('items\\'.$_GET['cat'].'\\'.$id);
                $items[$id]['cat'] = $_GET['cat'];
            }
        }
        $_SESSION['cat'] = $_GET['cat'];
    } else {
        foreach(loadDB('categories') as $cat => $name) {
            foreach(listDB('items\\'.$cat) as $id) {
                $items[$id] = loadDB('items\\'.$cat.'\\'.$id);
                $items[$id]['cat'] = $cat;
            }
        }
        $_SESSION['cat'] = '';
    }
    uasort($items, function($a, $b) {
        return $a['name'] <=> $b['name'];
    });
    include('inc/print.inc');
?>

