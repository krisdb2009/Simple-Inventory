<?php
if(isset($_GET['code'])) {
    if(isset($_GET['cat']) && isset($_GET['item'])) {
        header('location: ./?act=scanner&code='.$_GET['code'].'&cat='.$_GET['cat'].'&item='.$_GET['item']);
        exit;
    }
    ob_start();
    include('index.inc');
    $ob = ob_get_clean();
    $find = array(
    'act=item',
    '<body class="index textborder">',
    '<a href="?act=scanner" class="cbu button">',
    '<div class="cat">'
    );
    $replace = array(
    'act=associate&code='.$_GET['code'],
    '<body class="index textborder associate">',
    '<a href="./" class="cbu associate button">Exit Associate</a><a href="?act=scanner" class="cbu button">',
    '<div class="cat">'.$_GET['code'].'</div><div class="cat" style="display:none;">'
    );
    $output = str_replace($find, $replace, $ob);
    echo $output;
} else {
    header('location: ./');
}
?>