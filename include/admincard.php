<?php
  $version = "Pre-Alpha 1.2";
  $button = "이동하기 (Go!)";
 ?>
<!-- 유틸리티 나열 시작 -->
<hr>

<div class="card-deck main">
  <div class="card">
    <img class="card-img-top" src="test.jpg" alt="Card image cap">
    <div class="card-body text-center">
      <h3 class="card-text">후원 공지</h3>
      <p class="card-text"></p>
      <a href="/adminoph_notice" class="btn btn-info"><?php echo $button; ?></a>
    </div>
    <div class="card-footer">
      <small class="text-muted"><?php echo $version; ?></small>
    </div>
  </div>
  <div class="card">
    <img class="card-img-top" src="test.jpg" alt="Card image cap">
    <div class="card-body text-center">
      <h3 class="card-text">후원 신청 확인하기</h3>
      <p class="card-text"></p>
      <a href="/adminoph_checksupport" class="btn btn-info"><?php echo $button; ?></a>
    </div>
    <div class="card-footer">
      <small class="text-muted"><?php echo $version; ?></small>
    </div>
  </div>
  <div class="card">
    <img class="card-img-top" src="test.jpg" alt="Card image cap">
    <div class="card-body text-center">
      <h3 class="card-text">이 사이트 개발자에게 연락하는법</h3>
      <p class="card-text"></p>
      <a href="/adminoph_developer" class="btn btn-info">확인하기</a>
    </div>
    <div class="card-footer">
      <small class="text-muted"><?php echo $version; ?></small>
    </div>
  </div>
</div>
<!-- 유틸리티 나열 끝 -->
