### Create new table if not exists:

```
table @name {@structure};
```

Example:
```
table account {
  login: string,
  password: string
};
```

### Delete the table:

```
delete @name;
```

Example:
```
delete account;
```

### Insert a values into a table:

```
insert into: @name {@structure}; or
insert into: @name {@list};
```

Examples:
```
insert into: account {login: `adi`, password: `00000000`};
insert into: account {`adi`, `00000000`};
```


### Select query

```
select from: @name where: @filter;
```

Example:
```
select from: account where: .login = `adi`;

// the same
select from: account where: true;
select from: account where: 1;

// && and || binary operators
select from: account where: (.login = `adi` && .password = `00000000`) || .login = `michael`;
```

### Remove query

Removes column in the table:

```
remove from: @name where: @filter;
```

Example:
```
remove from: account where: .id = `00000000`;
```