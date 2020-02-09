<?php
  if(!$_SESSION['grade']==20151020)  {
    ?>
    <script>
      alert("권한이 없습니다! You don't have permission!");
      location.href='/';
    </script>
    <?php
    die();
  }
?>
