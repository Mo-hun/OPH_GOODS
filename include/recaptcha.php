<script src='https://www.google.com/recaptcha/api.js?render=6Lc-4pIUAAAAANLDd1-mfl5cVb_9SA0t7HYt6-YN'></script>
<script>
window.onload = function() {
    getElementById('button-id').addEventListener("click", function() {
        grecaptcha.ready(function() {
            grecaptcha.execute('6Lc-4pIUAAAAANLDd1-mfl5cVb_9SA0t7HYt6-YN', {action: 'recaptcha'}).then(function(token) {
                document.getElementById('form-id').innerHTML = '<input type="hidden" name="token" value="' + token + '"><input type="hidden" name="action" value="recaptcha">';
                document.getElementById('form-id').submit();
            });
        });
    })
}
</script>
