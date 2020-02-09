<!-- 네비바 시작 -->
  <nav class="navbar navbar-expand-sm navbar-light bg-white border border-top-0 border-right-0 border-left-0 border-info">
    <a class="navbar-brand" href="/">
      <img src="./logo.png" alt="logo" height="45">
    </a>
    <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarText" aria-controls="navbarText" aria-expanded="false" aria-label="Toggle navigation">
      <span class="navbar-toggler-icon"></span>
    </button>
    <div class="collapse navbar-collapse" id="navbarText">
      <ul class="navbar-nav mr-auto">
        <li class="nav-item">
          <a class="nav-link" href="/">메인 (Main)</a>
        </li>
        <li class="nav-item">
          <a class="nav-link" href="/support">후원 하기 (폼 작성) Supporting (Writing form)</a>
        </li>
        <li class="nav-item ">
            <a class="nav-link" href="/notice">후원 공지 (Notice)</a>
        </li>
        <?php
          if(isset($_SESSION['idx'])) {
          ?>
        <li class="nav-item">
          <a class="nav-link" href="/goods_my">내 후원 상태는? (My Order Status)</a>
        </li>

        <li class="nav-item">
          <a class="nav-link" href="/cs/">고객 센터 (Customer Service)</a>
        </li>
        <?php
      } ?>
      </ul>
      <?php
        if(isset($_SESSION['idx'])) {
            ?>
      <button type="button" onclick="location.href='/mypage'" class="btn btn-outline-info">마이페이지 (MyPage)</button>
      &nbsp;&nbsp;
      <button type="button" onclick="location.href='/logout'" class="btn btn-outline-info">로그아웃 (Sign out)</button>
            <?php
            if($_SESSION['grade']==20151020)  {
              ?>
              &nbsp;&nbsp;
              <button type="button" onclick="location.href='/adminoph'" class="btn btn-outline-info">관리자! 환영합니다!</button>
              <?php
            }
        } else {
       ?>
      <button type="button" onclick="location.href='/login'" class="btn btn-outline-info">로그인 (Sign in)</button>
      &nbsp;&nbsp;
      <button type="button" onclick="location.href='/join'" class="btn btn-outline-info">회원가입 (Sign up)</button>
      <?php
        }
       ?>
    </div>
  </nav>
<!-- 네비바 끝 -->
