//MQTT Control
var client = new Paho.MQTT.Client("great-lawyer.cloudmqtt.com", 443, "myclientid_" + parseInt(Math.random() * 100, 10));

client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;

var options = {
  useSSL: true,
  userName:'cboiwkvz', 
  password:'NYfafrwlNXIt',
  onSuccess:onConnect,
  onFailure:doFail,
  mqttVersion:4
}

$( document ).ready(function() {
  client.connect(options);
});


function onConnect() {
  // Once a connection has been made, make a subscription and send a message.
  console.log("onConnect");
  alert('GO!');
  client.subscribe("move/#");
}

function doFail(e){
  console.log(e);
}

// called when the client loses its connection
function onConnectionLost(responseObject) {
  if (responseObject.errorCode !== 0) {
    console.log("onConnectionLost:"+responseObject.errorMessage);
  }
}

// called when a message arrives
function onMessageArrived(message) {
  var msgTopic = message.destinationName.split('/')[0];
  var msgSubtopic = message.destinationName.split('/')[1];
  var msgJson = JSON.parse(message.payloadString);
  console.log(msgTopic);
  if(msgTopic == 'move'){  
    if( msgSubtopic == '1'){
      move1(msgJson.direction);
    }
    else if( msgSubtopic == '2'){
      move2(msgJson.direction);
    }
    else if( msgSubtopic == '3'){
      move3(msgJson.direction);
    }
    else if( msgSubtopic == '4'){
      move4(msgJson.direction);
    }
    else if( msgSubtopic == '5'){
      move5(msgJson.direction);
    }
    else if( msgSubtopic == '6'){
      move6(msgJson.direction);
    }
    else if( msgSubtopic == '7'){
      move7(msgJson.direction);
    }
    else if( msgSubtopic == '8'){
      move8(msgJson.direction);
    }
    else if( msgSubtopic == '9'){
      move9(msgJson.direction);
    }
    else if( msgSubtopic == '10'){
      move10(msgJson.direction);
    }
    else if( msgSubtopic == '11'){
      move11(msgJson.direction);
    }
    else if( msgSubtopic == '12'){
      move12(msgJson.direction);
    }
    else if( msgSubtopic == '13'){
      move13(msgJson.direction);
    }
    else if( msgSubtopic == '14'){
      move14(msgJson.direction);
    }
    else if( msgSubtopic == '15'){
      move15(msgJson.direction);
    }
  }
}

//Creates a new Messaging.Message Object and sends it to the HiveMQ MQTT Broker
var publish = function (payload, topic, qos) {
  var message = new Paho.MQTT.Message(payload);
  message.destinationName = topic;
  client.send(message);
}

//Game control
//Monkeys Position
var m1=480,
  m2=480,
  m3=480,
  m4=480,
  m5=480,
  m6=480,
  m7=480,
  m8=480,
  m9=480,
  m10=480,
  m11=480,
  m12=480,
  m13=480,
  m14=480,
  m15=480;

//Banana Position
var b1=240,
  b2=240,
  b3=240,
  b4=240,
  b5=240,
  b6=240,
  b7=240,
  b8=240,
  b9=240,
  b10=240,
  b11=240,
  b12=240,
  b13=240,
  b14=240,
  b15=240;

//Team Score
var s1=0,
  s2=0,
  s3=0,
  s4=0,
  s5=0,
  s6=0,
  s7=0,
  s8=0,
  s9=0,
  s10=0,
  s11=0,
  s12=0,
  s13=0,
  s14=0,
  s15=0;

function move1(direction) {  
  if(direction == '1'){
    if(m1>0){ 
      m1-=10;
      $("#monkey1").css("margin-top", m1);
      if(m1 === b1){
        s1+=100;
        $("#score1").text(s1);
        var randNum = Math.floor(Math.random()*480);
        b1 = randNum - (randNum%10);
        $("#banana1").css("display", "none");
        $("#monkey1").css("margin-left", -20);
        publish(JSON.stringify({'position':b1}), 'banana/1',0);
      }
    }
  }
  else if(direction == '2'){
    if(m1<480){
      m1+=10;
      $("#monkey1").css("margin-top", m1);
      if(m1 === b1){
        s1+=100;
        $("#score1").text(s1);
        var randNum = Math.floor(Math.random()*480);
        b1 = randNum - (randNum%10);
        $("#banana1").css("display", "none");
        $("#monkey1").css("margin-left", -20);
        publish(JSON.stringify({'position':b1}), 'banana/1',0);
      }
    }
  }
}


function move2(direction) {  
  if(direction == '1'){
    if(m2>0){ 
      m2-=10;
      $("#monkey2").css("margin-top", m2);
      if(m2 === b2){
        s2+=100;
        $("#score2").text(s2);
        var randNu = Math.floor(Math.random()*480);
        b2 = randNu - (randNu%10);
        $("#banana2").css("display", "none");
        $("#monkey2").css("margin-left", -20);
        publish(JSON.stringify({'position':b2}), 'banana/2',0);
      }
    }
  }
  else if(direction == '2'){
    if(m2<480){
      m2+=10;
      $("#monkey2").css("margin-top", m2);
      if(m2 === b2){
        s2+=100;
        $("#score2").text(s2);
        var randNu = Math.floor(Math.random()*480);
        b2 = randNu - (randNu%10);
        $("#banana2").css("display", "none");
        $("#monkey2").css("margin-left", -20);
        publish(JSON.stringify({'position':b2}), 'banana/2',0);
      }
    }
  }
}

function move3(direction) {  
  if(direction == '1'){
    if(m3>0){ 
      m3-=10;
      $("#monkey3").css("margin-top", m3);
      if(m3 === b3){
        s3+=100;
        $("#score3").text(s3);
        var randNu = Math.floor(Math.random()*480);
        b3 = randNu - (randNu%10);
        $("#banana3").css("display", "none");
        $("#monkey3").css("margin-left", -20);
        publish(JSON.stringify({'position':b3}), 'banana/3',0);
      }
    }
  }
  else if(direction == '2'){
    if(m3<480){
      m3+=10;
      $("#monkey3").css("margin-top", m3);
      if(m3 === b3){
        s3+=100;
        $("#score3").text(s3);
        var randNu = Math.floor(Math.random()*480);
        b3 = randNu - (randNu%10);
        $("#banana3").css("display", "none");
        $("#monkey3").css("margin-left", -20);
        publish(JSON.stringify({'position':b3}), 'banana/3',0);
      }
    }
  }
}

function move4(direction) {  
  if(direction == '1'){
    if(m4>0){ 
      m4-=10;
      $("#monkey4").css("margin-top", m4);
      if(m4 === b4){
        s4+=100;
        $("#score4").text(s4);
        var randNu = Math.floor(Math.random()*480);
        b4 = randNu - (randNu%10);
        $("#banana4").css("display", "none");
        $("#monkey4").css("margin-left", -20);
        publish(JSON.stringify({'position':b4}), 'banana/4',0);
      }
    }
  }
  else if(direction == '2'){
    if(m4<480){
      m4+=10;
      $("#monkey4").css("margin-top", m4);
      if(m4 === b4){
        s4+=100;
        $("#score4").text(s4);
        var randNu = Math.floor(Math.random()*480);
        b4 = randNu - (randNu%10);
        $("#banana4").css("display", "none");
        $("#monkey4").css("margin-left", -20);
        publish(JSON.stringify({'position':b4}), 'banana/4',0);
      }
    }
  }
}


function move5(direction) {  
  if(direction == '1'){
    if(m5>0){ 
      m5-=10;
      $("#monkey5").css("margin-top", m5);
      if(m5 === b5){
        s5+=100;
        $("#score5").text(s5);
        var randNu = Math.floor(Math.random()*480);
        b5 = randNu - (randNu%10);
        $("#banana5").css("display", "none");
        $("#monkey5").css("margin-left", -20);
        publish(JSON.stringify({'position':b5}), 'banana/5',0);
      }
    }
  }
  else if(direction == '2'){
    if(m5<480){
      m5+=10;
      $("#monkey5").css("margin-top", m5);
      if(m5 === b5){
        s5+=100;
        $("#score5").text(s5);
        var randNu = Math.floor(Math.random()*480);
        b5 = randNu - (randNu%10);
        $("#banana5").css("display", "none");
        $("#monkey5").css("margin-left", -20);
        publish(JSON.stringify({'position':b5}), 'banana/5',0);
      }
    }
  }
}

function move6(direction) {  
  if(direction == '1'){
    if(m6>0){ 
      m6-=10;
      $("#monkey6").css("margin-top", m6);
      if(m6 === b6){
        s6+=100;
        $("#score6").text(s6);
        var randNu = Math.floor(Math.random()*480);
        b6 = randNu - (randNu%10);
        $("#banana6").css("display", "none");
        $("#monkey6").css("margin-left", -20);
        publish(JSON.stringify({'position':b6}), 'banana/6',0);
      }
    }
  }
  else if(direction == '2'){
    if(m6<480){
      m6+=10;
      $("#monkey6").css("margin-top", m6);
      if(m6 === b6){
        s6+=100;
        $("#score6").text(s6);
        var randNu = Math.floor(Math.random()*480);
        b6 = randNu - (randNu%10);
        $("#banana6").css("display", "none");
        $("#monkey6").css("margin-left", -20);
        publish(JSON.stringify({'position':b6}), 'banana/6',0);
      }
    }
  }
}

function move7(direction) {  
  if(direction == '1'){
    if(m7>0){ 
      m7-=10;
      $("#monkey7").css("margin-top", m7);
      if(m7 === b7){
        s7+=100;
        $("#score7").text(s7);
        var randNu = Math.floor(Math.random()*480);
        b7 = randNu - (randNu%10);
        $("#banana7").css("display", "none");
        $("#monkey7").css("margin-left", -20);
        publish(JSON.stringify({'position':b7}), 'banana/7',0);
      }
    }
  }
  else if(direction == '2'){
    if(m7<480){
      m7+=10;
      $("#monkey7").css("margin-top", m7);
      if(m7 === b7){
        s7+=100;
        $("#score7").text(s7);
        var randNu = Math.floor(Math.random()*480);
        b7 = randNu - (randNu%10);
        $("#banana7").css("display", "none");
        $("#monkey7").css("margin-left", -20);
        publish(JSON.stringify({'position':b7}), 'banana/7',0);
      }
    }
  }
}

function move8(direction) {  
  if(direction == '1'){
    if(m8>0){ 
      m8-=10;
      $("#monkey8").css("margin-top", m8);
      if(m8 === b8){
        s8+=100;
        $("#score8").text(s8);
        var randNu = Math.floor(Math.random()*480);
        b8 = randNu - (randNu%10);
        $("#banana8").css("display", "none");
        $("#monkey8").css("margin-left", -20);
        publish(JSON.stringify({'position':b8}), 'banana/8',0);
      }
    }
  }
  else if(direction == '2'){
    if(m8<480){
      m8+=10;
      $("#monkey8").css("margin-top", m8);
      if(m8 === b8){
        s8+=100;
        $("#score8").text(s8);
        var randNu = Math.floor(Math.random()*480);
        b8 = randNu - (randNu%10);
        $("#banana8").css("display", "none");
        $("#monkey8").css("margin-left", -20);
        publish(JSON.stringify({'position':b8}), 'banana/8',0);
      }
    }
  }
}

function move9(direction) {  
  if(direction == '1'){
    if(m9>0){ 
      m9-=10;
      $("#monkey9").css("margin-top", m9);
      if(m9 === b9){
        s9+=100;
        $("#score9").text(s9);
        var randNu = Math.floor(Math.random()*480);
        b9 = randNu - (randNu%10);
        $("#banana9").css("display", "none");
        $("#monkey9").css("margin-left", -20);
        publish(JSON.stringify({'position':b9}), 'banana/9',0);
      }
    }
  }
  else if(direction == '2'){
    if(m9<480){
      m9+=10;
      $("#monkey9").css("margin-top", m9);
      if(m9 === b9){
        s9+=100;
        $("#score9").text(s9);
        var randNu = Math.floor(Math.random()*480);
        b9 = randNu - (randNu%10);
        $("#banana9").css("display", "none");
        $("#monkey9").css("margin-left", -20);
        publish(JSON.stringify({'position':b9}), 'banana/9',0);
      }
    }
  }
}

function move10(direction) {  
  if(direction == '1'){
    if(m10>0){ 
      m10-=10;
      $("#monkey10").css("margin-top", m10);
      if(m10 === b10){
        s10+=100;
        $("#score10").text(s10);
        var randNu = Math.floor(Math.random()*480);
        b10 = randNu - (randNu%10);
        $("#banana10").css("display", "none");
        $("#monkey10").css("margin-left", -20);
        publish(JSON.stringify({'position':b10}), 'banana/10',0);
      }
    }
  }
  else if(direction == '2'){
    if(m10<480){
      m10+=10;
      $("#monkey10").css("margin-top", m10);
      if(m10 === b10){
        s10+=100;
        $("#score10").text(s10);
        var randNu = Math.floor(Math.random()*480);
        b10 = randNu - (randNu%10);
        $("#banana10").css("display", "none");
        $("#monkey10").css("margin-left", -20);
        publish(JSON.stringify({'position':b10}), 'banana/10',0);
      }
    }
  }
}

function move11(direction) {  
  if(direction == '1'){
    if(m11>0){ 
      m11-=10;
      $("#monkey11").css("margin-top", m11);
      if(m11 === b11){
        s11+=100;
        $("#score11").text(s11);
        var randNu = Math.floor(Math.random()*480);
        b11 = randNu - (randNu%10);
        $("#banana11").css("display", "none");
        $("#monkey11").css("margin-left", -20);
        publish(JSON.stringify({'position':b11}), 'banana/11',0);
      }
    }
  }
  else if(direction == '2'){
    if(m11<480){
      m11+=10;
      $("#monkey11").css("margin-top", m11);
      if(m11 === b11){
        s11+=100;
        $("#score11").text(s11);
        var randNu = Math.floor(Math.random()*480);
        b11 = randNu - (randNu%10);
        $("#banana11").css("display", "none");
        $("#monkey11").css("margin-left", -20);
        publish(JSON.stringify({'position':b11}), 'banana/11',0);
      }
    }
  }
}

function move12(direction) {  
  if(direction == '1'){
    if(m12>0){ 
      m12-=10;
      $("#monkey12").css("margin-top", m12);
      if(m12 === b12){
        s12+=100;
        $("#score12").text(s12);
        var randNu = Math.floor(Math.random()*480);
        b12 = randNu - (randNu%10);
        $("#banana12").css("display", "none");
        $("#monkey12").css("margin-left", -20);
        publish(JSON.stringify({'position':b12}), 'banana/12',0);
      }
    }
  }
  else if(direction == '2'){
    if(m12<480){
      m12+=10;
      $("#monkey12").css("margin-top", m12);
      if(m12 === b12){
        s12+=100;
        $("#score12").text(s12);
        var randNu = Math.floor(Math.random()*480);
        b12 = randNu - (randNu%10);
        $("#banana12").css("display", "none");
        $("#monkey12").css("margin-left", -20);
        publish(JSON.stringify({'position':b12}), 'banana/12',0);
      }
    }
  }
}

function move13(direction) {  
  if(direction == '1'){
    if(m13>0){ 
      m13-=10;
      $("#monkey13").css("margin-top", m13);
      if(m13 === b13){
        s13+=100;
        $("#score13").text(s13);
        var randNu = Math.floor(Math.random()*480);
        b13 = randNu - (randNu%10);
        $("#banana13").css("display", "none");
        $("#monkey13").css("margin-left", -20);
        publish(JSON.stringify({'position':b13}), 'banana/13',0);
      }
    }
  }
  else if(direction == '2'){
    if(m13<480){
      m13+=10;
      $("#monkey13").css("margin-top", m13);
      if(m13 === b13){
        s13+=100;
        $("#score13").text(s13);
        var randNu = Math.floor(Math.random()*480);
        b13 = randNu - (randNu%10);
        $("#banana13").css("display", "none");
        $("#monkey13").css("margin-left", -20);
        publish(JSON.stringify({'position':b13}), 'banana/13',0);
      }
    }
  }
}

function move14(direction) {  
  if(direction == '1'){
    if(m14>0){ 
      m14-=10;
      $("#monkey14").css("margin-top", m14);
      if(m14 === b14){
        s14+=100;
        $("#score14").text(s14);
        var randNu = Math.floor(Math.random()*480);
        b14 = randNu - (randNu%10);
        $("#banana14").css("display", "none");
        $("#monkey14").css("margin-left", -20);
        publish(JSON.stringify({'position':b14}), 'banana/14',0);
      }
    }
  }
  else if(direction == '2'){
    if(m14<480){
      m14+=10;
      $("#monkey14").css("margin-top", m14);
      if(m14 === b14){
        s14+=100;
        $("#score14").text(s14);
        var randNu = Math.floor(Math.random()*480);
        b14 = randNu - (randNu%10);
        $("#banana14").css("display", "none");
        $("#monkey14").css("margin-left", -20);
        publish(JSON.stringify({'position':b14}), 'banana/14',0);
      }
    }
  }
}

function move15(direction) {  
  if(direction == '1'){
    if(m15>0){ 
      m15-=10;
      $("#monkey15").css("margin-top", m15);
      if(m15 === b15){
        s15+=100;
        $("#score15").text(s15);
        var randNu = Math.floor(Math.random()*480);
        b15 = randNu - (randNu%10);
        $("#banana15").css("display", "none");
        $("#monkey15").css("margin-left", -20);
        publish(JSON.stringify({'position':b15}), 'banana/15',0);
      }
    }
  }
  else if(direction == '2'){
    if(m15<480){
      m15+=10;
      $("#monkey15").css("margin-top", m15);
      if(m15 === b15){
        s15+=100;
        $("#score15").text(s15);
        var randNu = Math.floor(Math.random()*480);
        b15 = randNu - (randNu%10);
        $("#banana15").css("display", "none");
        $("#monkey15").css("margin-left", -20);
        publish(JSON.stringify({'position':b15}), 'banana/15',0);
      }
    }
  }
}