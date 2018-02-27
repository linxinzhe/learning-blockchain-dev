<?php

function get_lines_file($file){
	$result=array();
	$contents=file_get_contents($file);
	$contents=explode(chr(10),$contents);
	foreach($contents as $item){
		$item = str_replace(chr(13),'',$item);
		if(strlen($item)>0){
			array_push($result,$item);
		}
	}
	return $result;
}

// $digests=array();  //Here for simulate raw all tx digest.txt
// foreach (range(1,100) as $number)
// 	$digests[]=hash('sha256',rand());
// //var_dump($digests);
// //bar_dump(get_Merkle_root($digests));

// $c='';
// foreach($digests as $b)
// 	$c .= $b.chr(10);
// echo $c;  // php lecture8_merkle_tree.php > ../digest.txt

$x=get_lines_file('../digest.txt');
// var_dump($x);

function get_Merkle_root($digests){
	if(count($digests)==1){
		echo sprintf('case #1:%d%c',count($digests),10);
		return $digests[0];
	}

	if(count($digests)%2){  //odd then copy the last one
		echo sprintf('case #2:%d%c',count($digests),10);
		$item=$digests[count($digests)-1];
		array_push($digests,$item);
		return get_Merkle_root($digests);
	}

	echo sprintf('case #3: %d%c',count($digests),10);
	for($i=0,$s=count($digests)/2;$i<$s;$i++){
		$a=array_shift($digests);  // pop from left
		$b=array_shift($digests);	// pop from left
		array_push($digests,hash('sha256',$a,$b));  //digest insert to right
	}

	return get_Merkle_root($digests);

	// equivalent but with a new array
	// $reduced=array();
	// $i=0;
	// while($i<count($digests)){
	// 	$merged=sprintf("%s%s",$digests[i],$digests[i+1]);
	// 	array_push($reduced,hash('sha256',$merged));
	// 	$i+=2;
	// }
	// return get_Merkle_root($digests); 
}

$digest=get_Merkle_root($x);
var_dump($digest);