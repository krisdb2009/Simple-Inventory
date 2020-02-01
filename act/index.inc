<?php
//Cedar Point//Dylan Bickerstaff//2016//CFIT Inventory
    $categoryName = 'All Categories';
    $catItems = array();
    if(isset($_GET['cat']) && !empty($_GET['cat'])) {
        $cats = loadDB('categories');
        if(isset($cats[$_GET['cat']])) {
            $categoryName = $cats[$_GET['cat']];
            foreach(listDB('items\\'.$_GET['cat']) as $id) {
                $catItems[$id] = loadDB('items\\'.$_GET['cat'].'\\'.$id);
                $catItems[$id]['cat'] = $_GET['cat'];
            }
        }
        $_SESSION['cat'] = $_GET['cat'];
    } else {
        foreach(loadDB('categories') as $cat => $name) {
            foreach(listDB('items\\'.$cat) as $id) {
                $catItems[$id] = loadDB('items\\'.$cat.'\\'.$id);
                $catItems[$id]['cat'] = $cat;
            }
        }
        $_SESSION['cat'] = '';
    }
    uasort($catItems, function($a, $b) {
        return $a['name'] <=> $b['name'];
    });
?>
<html>
    <head>
        <title>Simple Inventory</title>
        <link rel="stylesheet" type="text/css" href="static/style.css">
        <meta content='width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=0' name='viewport' />
		<script src="./static/zxing.qrcodereader.min.js"></script>
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
		<script>
			window.addEventListener('load', function() {
				const codeReader = new ZXing.BrowserQRCodeReader();
				codeReader.getVideoInputDevices().then((videoInputDevices) => {
					const sourceSelect = document.getElementById('sourceSelect');
					const firstDeviceId = videoInputDevices[0].deviceId;
					if (videoInputDevices.length > 1) {
						videoInputDevices.forEach((element)=>{
							const sourceOption = document.createElement('option');
							sourceOption.text = element.label;
							sourceOption.value = element.deviceId;
							sourceSelect.appendChild(sourceOption);
						});
						const sourceSelectPanel = document.getElementById('sourceSelectPanel');
						sourceSelectPanel.style.display = 'block';
					}
					document.getElementById('scanbtn').addEventListener('click', () => {
						document.getElementById('barcode').classList.add('visible');
						codeReader.decodeFromInputVideoDevice(firstDeviceId, 'video').then((result) => {
							window.location = './?act=scanner&code='+result.text;
						});
					});
					document.getElementById('resetButton').addEventListener('click', ()=>{
						codeReader.reset();
						document.getElementById('barcode').classList.remove('visible');
					});
				});
			});
		</script>
    </head>
    <body class="index textborder">
		<div id="barcode">
			<div>
				<span>Barcode Scanner</span>
				<a class="button" id="resetButton">X</a>
			</div>
			<video id="video" width="300" height="200"></video>
			<div id="camera">
				<label>Camera:</label>
				<select id="sourceSelect" style="max-width:400px"></select>
			</div>
		</div>
        <div class="cat"><?php echo $categoryName; ?></div>
        <div class="lb">
            <div class="lbe ttl">
                <span class="i">Item</span><span class="c">Count</span>
            </div>
            <?php
                foreach($catItems as $key => $val) {
                    $level = 'black';
                    if($val['count'] <= 3) {
                        $level = 'orange';
                    }
                    if($val['count'] == 0) {
                        $level = 'red';
                    }
                    echo '<a href="?act=item&cat='.$val['cat'].'&item='.$key.'"><div class="lbe"><span style="color:'.$level.';" class="i">'.$val['name'].'</span><span class="c">'.$val['count'].'</span></div></a>';
                }
            ?>
        </div>
        <div class="rb">
        <?php
            foreach($catItems as $key => $val) {
                $level = 'black';
                if($val['count'] <= 3) {
                    $level = 'orange';
                }
                if($val['count'] == 0) {
                    $level = 'red';
                }
                echo '<a href="?act=item&cat='.$val['cat'].'&item='.$key.'"><div style="background-image:url(\'./DB/static/'.$val['img'].'\');" class="box">'.$val['name'].'<span style="color:'.$level.';">'.$val['count'].'</span></div></a>';
            }
        ?>
        </div>
        <div class="bl">
            <a href="?act=ccategor" class="cbu cc button">Change Category</a>
            <a href="?act=additems&cat=<?php echo $_SESSION['cat']; ?>" class="cbu button">Add Items</a>
            <a href="?act=printcat&cat=<?php echo $_SESSION['cat']; ?>" class="cbu button">Print List</a>
			<a id="scanbtn" class="cbu button">Scan</a>
        </div>
    </body>
</html>
