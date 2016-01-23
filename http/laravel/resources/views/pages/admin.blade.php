@extends('template')
@section('content')

    <div class="container wrap margin-top">
        <div class="row">
            <div class="panel panel-default">
                <div class="panel-heading">Admin panel</div>
                <div class="panel-body">
                    <form role="form" method="POST" action="/admin/update">
                        <input type="hidden" name="_token" value="{{ csrf_token() }}">

                        <div class="form-group">

                            <label for="sel1">Select users:</label>
                            <select onclick="fill_form(this.value);" name="name" class="form-control" id="sel1"
                                    value="test">
                                @foreach($users as $user)
                                    <option value="{{ $user->id }}">{{ $user->name }}</option>
                                @endforeach
                            </select>
                        </div>
                        <div class="form-group">
                            <label for="id">Id:</label>
                            <input name="id" type="number" class="form-control" id="id" readonly>
                        </div>
                        <div class="form-group">
                            <label for="email">Email:</label>
                            <input name="email" type="email" class="form-control" id="email" readonly>
                        </div>
                        <div class="form-group">
                            <label for="sel2">Select role:</label>
                            <select name="role" class="form-control" id="sel2">
                                <option>admin</option>
                                <option>customer</option>
                                <option>vehicle maintainer</option>
                            </select>
                        </div>
                        <br>

                        <div class="form-group">
                            <button type="submit" class="btn btn-default">Update</button>
                        </div>
                    </form>
                    @if(Session::has('message'))
                        <br>
                        <div class="alert alert-success">
                            <strong>Success!</strong> {{ Session::get('message') }}
                        </div>
                    @endif
                </div>
            </div>

        </div>
    </div>

    <script>
        var users = <?php echo json_encode($users); ?>;

        function get_user(id) {
            for (var i = 0; i < users.length; i++) {
                var user_obj = users[i];
                if (user_obj.id == id) {
                    return user_obj;
                }
            }
        }

        function fill_form(id) {
            var user = get_user(id);

            $("#sel1").val(id);
            $("#id").val(id);
            $("#email").val(user.email);
            $("#sel2").val(user.role);
        }

    </script>
    <script>fill_form(1);</script>
@stop