<?php
if(isset($_GET['code'])) {
    if(empty($_GET['code'])) {
        header('location: ./');
        exit;
    }
    if(isset($_GET['associate']) && !isset($_GET['un'])) {
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
                        } elseif(isset($_GET['un'])) {
                            unset($item['codes'][$k]);
                            putDB($item, 'items\\'.$cat.'\\'.$itemid);
                            header('location: ./?act=scanner&un&associate&code='.$_GET['code']);
                        } else {
                            header('location: ./?act=item&cat='.$cat.'&item='.$itemid);
                        }
                        exit;
                    }
                }
            }
        }
    }
    if(isset($_GET['cat']) && isset($_GET['item']) && !isset($_GET['un'])) {
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
    } elseif(isset($_GET['un'])) {
        header('location: ./?act=more');
    } else  {
        header('location: ./?act=associate&code='.$_GET['code']);
    }
    exit;
}
$un = '';
$aun = '';
if(isset($_GET['un'])) {
    $un = 'un';
    $aun = '&un';
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
                window.location = './?act=scanner<?php echo $aun; ?>&associate&code='+keys;
            } else {
                keys = keys+e.key;
            }
        };
        </script>
    </head>
    <body class="scanner textborder tacenter">
        <br><br><br>
        <h1>Scan or type a barcode number then press enter to <?php echo $un; ?>associate.</h1>
        <br><br>
        <a class="button" href="./?act=more">Cancel</a>
    </body>
</html>
