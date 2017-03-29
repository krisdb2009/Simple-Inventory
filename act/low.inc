<?php
$title = 'Low Items';
$items = array();
$c = 0;
foreach(loadDB('categories') as $id  => $name) {
    foreach(listDB('items\\'.$id) as $iid) {
        $item = loadDB('items\\'.$id.'\\'.$iid);
        if(isset($item['count']) && $item['count'] <= 3) {
            $c++;
            $items[$c] = array();
            $items[$c]['count'] = $item['count'];
            $items[$c]['name'] = $item['name'];
        }
    }
}
include('inc/print.inc');
?>