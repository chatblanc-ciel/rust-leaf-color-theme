<script>
  let toDoItems = [
                    {text: 'ゴミ出し', status: true},
                    {text: 'プログラミング学習', status: false},
                    {text: '友達に連絡', status: false}
                  ];

  function removeFromList(i) {
    toDoItems.splice(i, 1)
    toDoItems = toDoItems
  }
</script>

<h1>タスクリストアプリケーションへようこそ!</h1>
<h3>名前を入力してください。</h3>
<form on:submit|preventDefault={handleSubmit}>
  <div>
    <input bind:value={lastName} type="text" placeholder="姓" required>
  </div>
  <div>
    <input bind:value={firstName} type="text" placeholder="名" required>
  </div>
  <button type="submit">タスク管理を始める</button>
</form>
{#each toDoItems as item, index}
  <div class="toDoItems">
    <input bind:checked={item.status} type="checkbox">
    <span class:checked={item.status}>{item.text}</span>
    <button on:click={() => removeFromList(index)}>削除</button>
    <br/>
  </div>
{/each} 

<style>
  .checked {
      text-decoration: line-through;
  }
  .toDoItems {
      text-align: left;
  }
</style>