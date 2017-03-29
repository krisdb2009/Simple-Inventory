<?php
if(isset($_GET['code'])) {
    if(empty($_GET['code'])) {
        header('location: ./');
        exit;
    }
    if(isset($_GET['associate'])) {
        header('location: ./?act=associate&code='.$_GET['code']);
        exit();
    }
    foreach(loadDB('categories') as $cat => $name) {
        foreach(listDB('items\\'.$cat) as $itemid) {
            $item = loadDB('items\\'.$cat.'\\'.$itemid);
            if(isset($item['codes'])) {
                foreach($item['codes'] as $k => $code) {
                    if($code == $_GET['code']) {
                        if(isset($_GET['cat']) && isset($_GET['item'])) {
                            unset($item['codes'][$k]);
                            putDB($item, 'items\\'.$cat.'\\'.$itemid);
                            header('location: ./?act=scanner&code='.$_GET['code'].'&cat='.$_GET['cat'].'&item='.$_GET['item']);
                        } else {
                            header('location: ./?act=item&cat='.$cat.'&item='.$itemid);
                        }
                        exit;
                    }
                }
            }
        }
    }
    if(isset($_GET['cat']) && isset($_GET['item'])) {
        $item = loadDB('items\\'.$_GET['cat'].'\\'.$_GET['item']);
        if(!empty($item)) {
            if(!isset($item['codes'])) {
                $item['codes'] = array();
            }
            array_push($item['codes'], $_GET['code']);
            putDB($item, 'items\\'.$_GET['cat'].'\\'.$_GET['item']);
            header('location: ./?act=item&cat='.$_GET['cat'].'&item='.$_GET['item']);
        } else {
            header('location: ./');
        }
    } else {
        header('location: ./?act=associate&code='.$_GET['code']);
    }
    exit;
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
                window.location = './?act=scanner&associate&code='+keys;
            } else {
                keys = keys+e.key;
            }
        };
        </script>
    </head>
    <body class="scanner textborder tacenter">
        <br><br><br>
        <h1>Scan or type a barcode number then press enter to associate.</h1>
    </body>
</html>
