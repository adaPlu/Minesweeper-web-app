var counter = 0;
var mines = 0;
var gameOver = 0;
var newGame = 0;
var timerID = 0;
var faceTimerID = 0;
//1-Loss, 2-Win  Needed?
function checkState(gameState){
	
	if(gameState == 1){
		//alert("Game Over! Hit Reset Game to Play Again!");
		clearInterval(faceTimerID);
		$('#face').html('<img src="faceSad.png" style="width:50px; height:50px; padding-bottom:10px;">');
	}
	else if(gameState == 2){
		//alert("Game Over! Hit Reset Game to Play Again!");
	}
}

function updateGrid(r, c, state){
	var sel = "#" + r.toString()+ "-" + c.toString();
	var i;
	
	
	if(state == 9){
		$(sel).html('<img src="unopened.png" style="width:50px; height:50px">');
	}
	else if (state == 1){
		$(sel).html('<img src="1.png" style="width:50px; height:50px">');
	}
	else if (state == 2){
		$(sel).html('<img src="2.png" stjpgyle="width:50px; height:50px">');
	}
	else if (state == 3){
		$(sel).html('<img src="3.png" style="width:50px; height:50px">');
	}
	else if (state == 4){
		$(sel).html('<img src="4.png" style="width:50px; height:50px">');
	}
	else if (state == 5){
		$(sel).html('<img src="5.png" stjpgyle="width:50px; height:50px">');
	}
	else if (state == 6){
		$(sel).html('<img src="6.png" style="width:50px; height:50px">');
	}
	else if (state == 7){
		$(sel).html('<img src="7.png" style="width:50px; height:50px">');
	}
	else if (state == 8){
		$(sel).html('<img src="8.png" stjpgyle="width:50px; height:50px">');
	}
	else if (state == 10){
		$(sel).html('<img src="blank.png" style="width:50px; height:50px">');

	}
	else if (state == 11){
		$(sel).html('<img src="flag.png" style="width:50px; height:50px">');
	}
	else if (state == 12){
		$(sel).html('<img src="mine.png" style="width:50px; height:50px">');
	}
	else if (state == 13){
		$(sel).html('<img src="pit.jpg" stjpgyle="width:50px; height:50px">');
	}
	else if (state == 14){
		$(sel).html('<img src="qmark.png" stjpgyle="width:50px; height:50px">');
	}

}

function createGrid(data){
	var result = "";

	for (var i in data){
		var cr = "<tr>";

		for (var j in data[i]){
			cr = cr + "<td id=\"" + i.toString()+ "-" + j.toString() + "\"></td>"
		}

		cr = cr + "</tr>\n";
		result = result + cr;
	}

	$("#grid").html(result);
}

function timeIt(){
	if(gameOver == 0){
		if(counter < 999)
			counter++;
		if(counter < 10)
			$('#timer').html("00" + counter);
		else if(counter < 100)
			$('#timer').html("0" + counter);
		else
			$('#timer').html(counter);
	}
}

function clickFace(){
	$('#face').html('<img src="smile.png" style="width:50px; height:50px; padding-bottom:10px;">');	
}

$(document).ready(function(){
	
	$.get("/init", {}, function(response){
		counter = 0;
		var data = JSON.parse(response);
		gameOver = data["gameState"];
		$('#timer').html('000');
		$('#face').html('<img src="smile.png" style="width:50px; height:50px; padding-bottom:10px;">');
		mines = data["mines"];
		$("#mines").html("0" + mines);
		createGrid(data["board"]);
		for (var row in data["board"]){
			for (var col in data["board"][row]){
				updateGrid(row, col, data["board"][row][col]);
			}
		}
		for(var i in data["board"]){
			var cr = "<tr>";
			for(var j in data["board"][i]){
				var theID = "#" + i.toString() +"-" + j.toString();
				$(theID).click({row: i, col: j}, function(e){
					clearInterval(faceTimerID);
					if(newGame == 0){
						timerID = setInterval('timeIt()', 1000);
						newGame = 1;
					}
					var x = e.data.row;
					var y = e.data.col;		
					var location = {"x": x, "y":  y, "btn" : "left"};
					$.get("/handle", location, function(response){
						$('#face').html('<img src="click.png" style="width:50px; height:50px; padding-bottom:10px;">');
						faceTimerID = setInterval('clickFace()',500);
						var data = JSON.parse(response);
						mines = data["mines"];
						if(mines < 10)
							$("#mines").html("00" + mines);
						else
							$("#mines").html("0" + mines);
						for (var row in data["board"]){
							for (var col in data["board"][row]){
								updateGrid(row, col, data["board"][row][col]);
							}
						}
						
						gameOver = data["gameState"];
						checkState(data["gameState"]);
					});
				});
				$(theID).contextmenu({row: i, col: j},function(e){
					e.preventDefault();
					if(newGame == 0){
						timerID = setInterval('timeIt()', 1000);
						newGame = 1;
					}
					var x = e.data.row;
					var y = e.data.col;
					var location = {"x": x, "y": y, "btn" : "right"};
					$.get("/handle", location, function(response){
						var data = JSON.parse(response);
						mines = data["mines"];
						if(mines < 10)
							$("#mines").html("00" + mines);
						else
							$("#mines").html("0" + mines);
						for (var row in data["board"]){
							for (var col in data["board"][row]){
								updateGrid(row, col, data["board"][row][col]);
							}
						}
						gameOver = data["gameState"];
						checkState(data["gameState"]);
					});
				});
			} 
		}
		
	});
	$('#face').html('<img src="smile.png" style="width:50px; height:50px; padding-bottom:10px;">');
	$("#resetBtn").click(function(){
		$.get("/init", {}, function(response){
			counter = 0;
			newGame = 0;
			clearInterval(timerID);
			var data = JSON.parse(response);
			gameOver = data["gameState"];
			$('#timer').html('000');
			$('#face').html('<img src="smile.png" style="width:50px; height:50px; padding-bottom:10px;">');
			mines = data["mines"];
			$("#mines").html("0" + mines.toString());
			createGrid(data["board"]);
			for (var row in data["board"]){
				for (var col in data["board"][row]){
					updateGrid(row, col, data["board"][row][col]);
				}
			}
			for(var i in data["board"]){
				var cr = "<tr>";
				for(var j in data["board"][i]){
					var theID = "#" + i.toString() +"-" + j.toString();
					$(theID).click({row: i, col: j}, function(e){
						clearInterval(faceTimerID);
						if(newGame == 0){
							timerID = setInterval('timeIt()', 1000);
							newGame = 1;
						}
						var x = e.data.row;
						var y = e.data.col;		
						var location = {"x": x, "y":  y, "btn" : "left"};
						$.get("/handle", location, function(response){
							$('#face').html('<img src="click.png" style="width:50px; height:50px; padding-bottom:10px;">');
							faceTimerID = setInterval('clickFace()',500);
							var data = JSON.parse(response);
							mines = data["mines"];
							if(mines < 10)
								$("#mines").html("00" + mines);
							else
								$("#mines").html("0" + mines);
							for (var row in data["board"]){
								for (var col in data["board"][row]){
									updateGrid(row, col, data["board"][row][col]);
								}
							}
							gameOver = data["gameState"];
							checkState(data["gameState"]);
						});
					});
					$(theID).contextmenu({row: i, col: j},function(e){
						e.preventDefault();
						if(newGame == 0){
							timerID = setInterval('timeIt()', 1000);
							newGame = 1;
						}
						var x = e.data.row;
						var y = e.data.col;
						var location = {"x": x, "y": y, "btn" : "right"};
						$.get("/handle", location, function(response){
							var data = JSON.parse(response);
							mines = data["mines"];
							if(mines < 10)
								$("#mines").html("00" + mines);
							else
								$("#mines").html("0" + mines);
							for (var row in data["board"]){
								for (var col in data["board"][row]){
									updateGrid(row, col, data["board"][row][col]);

								}
							}
							gameOver = data["gameState"];
							checkState(data["gameState"]);
						});
					});
				}	
			}
		});
	});
});