<?php
  $version = "Open Beta Test 1.0";
  $button = "이동하기 (Go!)";
 ?>
<!-- 유틸리티 나열 시작 -->
<hr>

<div class="card-deck main">
  <div class="card">
    <img class="card-img-top" src="test.jpg" alt="Card image cap">
    <div class="card-body text-center">
      <h3 class="card-text">후원 하기 (폼 작성)<br>Supporting (Writing form)</h3>
      <p class="card-text"></p>
      <a href="/support" class="btn btn-info"><?php echo $button; ?></a>
    </div>
    <div class="card-footer">
      <small class="text-muted"><?php echo $version; ?></small>
    </div>
  </div>
  <div class="card">
    <img class="card-img-top" src="test.jpg" alt="Card image cap">
    <div class="card-body text-center">
      <h3 class="card-text">후원 공지<br>Notice</h3>
      <p class="card-text"></p>
      <a href="/notice" class="btn btn-info"><?php echo $button; ?></a>
    </div>
    <div class="card-footer">
      <small class="text-muted"><?php echo $version; ?></small>
    </div>
  </div>
  <div class="card">
    <img class="card-img-top" src="test.jpg" alt="Card image cap">
    <div class="card-body text-center">
      <h3 class="card-text">내 후원 상태는?<br>My Order Status</h3>
      <p class="card-text"></p>
      <a href="/goods_my" class="btn btn-info"><?php echo $button; ?></a>
    </div>
    <div class="card-footer">
      <small class="text-muted"><?php echo $version; ?></small>
    </div>
  </div>
  <div class="card">
    <div class="card-body text-center">
      <a class="twitter-timeline" href="https://twitter.com/TEAM_OPH?ref_src=twsrc%5Etfw" height="350"></a> <script async src="https://platform.twitter.com/widgets.js" charset="utf-8"></script>
    </div>
    <div class="card-footer">
      <small class="text-muted"><?php echo $version; ?></small>
    </div>
  </div>
</div>
<!-- 유틸리티 나열 끝 -->
